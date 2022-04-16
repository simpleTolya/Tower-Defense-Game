#include <iostream>
#include <QThread>
#include <QMessageBox>
#include <ui_mainwindow.h>
#include "headers/mainwindow.h"
#include "headers/enemy.h"
#include "headers/bullet.h"
#include "headers/firetower.h"
#include "headers/earthtower.h"
#include "headers/icetower.h"
#include "headers/firetowerbutton.h"
#include "headers/icetowerbutton.h"
#include "headers/earthtowerbutton.h"

const QPoint MainWindow::respawn_point(LineCount / 2, 0);
const QPoint MainWindow::enemy_target(LineCount / 2, FieldInLineCount - 1);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    spawnTimer = new QTimer;
    current = QPoint(-1, -1);

    // menu

    QAction *info = new QAction("Info", this);
    QAction *about = new QAction("About", this);
    QAction *quit = new QAction("Quit", this);

    QMenu *menu = ui->menubar->addMenu("Menu");
    menu->addAction(info);
    menu->addAction(about);
    menu->addAction(quit);

    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(about, &QAction::triggered, this, &MainWindow::makeAbout);
    connect(info, &QAction::triggered, this, &MainWindow::makeInfo);


    // tower buttons panel
    scene2 = new QGraphicsScene;
    ui->graphicsView_2->setScene(scene2);
    ui->graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	scene2->addPixmap(QPixmap(ButtonPanelImagePath))->setPos(0, -200);
	scene2->addPixmap(QPixmap(ButtonPanelImagePath))->setPos(0, -100);
	scene2->addPixmap(QPixmap(ButtonPanelImagePath))->setPos(0, 303);
	scene2->addPixmap(QPixmap(ButtonPanelImagePath))->setPos(0, 403);
    TowerButton * towerButton = new EarthTowerButton;
    scene2->addItem(towerButton);
    towerButton->setPos(0, 0);
    connect(towerButton, &TowerButton::clicked, this, &MainWindow::makeTower);

    towerButton = new FireTowerButton;
    scene2->addItem(towerButton);
    towerButton->setPos(0, 101);
    connect(towerButton, &TowerButton::clicked, this, &MainWindow::makeTower);

    towerButton = new IceTowerButton;
    scene2->addItem(towerButton);
    towerButton->setPos(0, 202);
    connect(towerButton, &TowerButton::clicked, this, &MainWindow::makeTower);

    // traectory
    traectory = new QList <QPoint>;
    traectory->push_back(QPoint(15, 4));

    // big game field
    for (int i=0; i < LineCount; i++) {
        for (int j=0; j < FieldInLineCount; j++) {
            Field * field = new Field;
            helping_fields[i][j] = EMPTY_CELL_MAYBE_TOWER;
            fields[i][j] = field;
            connect(fields[i][j], &AbstractField::clicked, this, &MainWindow::chooseField);

            scene->addItem(field);
            field->setPos(Field::FIELD_WIDTH * j, Field::FIELD_HEIGHT * i);
        }
    }
    helping_fields[respawn_point.x()][respawn_point.y()] = EMPTY_CELL_WITHOUT_TOWER;
    helping_fields[enemy_target.x()][enemy_target.y()] = EMPTY_CELL_WITHOUT_TOWER;

    // make walls
	scene->addPixmap(QPixmap(TopLeftAngleImagePath))->
            setPos(-AbstractField::FIELD_WIDTH, -AbstractField::FIELD_HEIGHT);
	scene->addPixmap(QPixmap(TopRightAngleImagePath))->
            setPos(FieldInLineCount * AbstractField::FIELD_WIDTH, -AbstractField::FIELD_HEIGHT);
	scene->addPixmap(QPixmap(DownLeftAngleImagePath))->
            setPos(-AbstractField::FIELD_WIDTH, LineCount * AbstractField::FIELD_HEIGHT);
	scene->addPixmap(QPixmap(DownRightAngleImagePath))->
            setPos(FieldInLineCount * AbstractField::FIELD_WIDTH, LineCount * AbstractField::FIELD_HEIGHT);

    for (int i=0; i < LineCount; i++) {
		scene->addPixmap(QPixmap(VerWallImagePath))->
                setPos(-AbstractField::FIELD_WIDTH, AbstractField::FIELD_HEIGHT * i);
		scene->addPixmap(QPixmap(VerWallImagePath))->
                setPos(FieldInLineCount * AbstractField::FIELD_WIDTH, AbstractField::FIELD_HEIGHT * i);
    }
    for (int i=0; i < FieldInLineCount; i++) {
		scene->addPixmap(QPixmap(HorWallImagePath))->
                setPos(AbstractField::FIELD_WIDTH * i, -AbstractField::FIELD_HEIGHT);
		scene->addPixmap(QPixmap(HorWallImagePath))->
                setPos(AbstractField::FIELD_WIDTH * i, LineCount * AbstractField::FIELD_HEIGHT);
    }

    // round
    mustBeSpawned = 0;
    livedEnemyCount = 0;
    level = 1;
    roundTimer = new QTimer;
    connect(roundTimer, &QTimer::timeout, this, &MainWindow::beginRound);
    gameBegin();
}



MainWindow::~MainWindow()
{
    delete roundTimer;
    delete spawnTimer;
    delete scene;
    delete scene2;
    delete traectory;
    for (int i=0; i < LineCount; i++) {
        for (int j=0; j < FieldInLineCount; j++) {
            delete fields[i][j];
        }
    }
    delete ui;
}

void MainWindow::fire(QPointF begin, Enemy *end, int damage, QPixmap & bulletImage) {
    Bullet * bull = new Bullet(begin, end, damage, bulletImage);
    scene->addItem(bull);
}

void MainWindow::addTower(int column, int string, int towerType) {
    if (is_rest and helping_fields[string][column] == EMPTY_CELL_MAYBE_TOWER) {
        scene->removeItem(fields[string][column]);
        delete fields[string][column];
        Tower * tower;
        switch (towerType) {
            case Tower::EARTH_TOWER_TYPE:
                tower = new EarthTower;
                break;
            case Tower::FIRE_TOWER_TYPE:
                tower = new FireTower;
                break;
            case Tower::ICE_TOWER_TYPE:
                tower = new IceTower;
                break;
        }
        connect(tower, &Tower::fire, this, &MainWindow::fire);
        fields[string][column] = tower;
        helping_fields[string][column] = BUSY_CELL;
        tower->setPos(Field::FIELD_WIDTH * column, Field::FIELD_HEIGHT * string);
        scene->addItem(tower);
        update_fields_traectory();
    }
}

void MainWindow::deleteTower(int column, int string) {
    if (is_rest and helping_fields[string][column] == BUSY_CELL) {
        scene->removeItem(fields[string][column]);
        delete fields[string][column];
        Field * field = new Field;
        fields[string][column] = field;
        helping_fields[string][column] = EMPTY_CELL_WITHOUT_TOWER;
        field->setPos(Field::FIELD_WIDTH * column, Field::FIELD_HEIGHT * string);
        scene->addItem(field);
        update_fields_traectory();
    }
}

void MainWindow::makeWaysArray(QPoint start, int ***array, int width, int height) {

    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            if ((*array)[i][j] != BUSY_CELL) {
                (*array)[i][j] = EMPTY_CELL_WITHOUT_TOWER;
            }
        }
    }

    QList <QPair<QPoint, int>> queue;
    QPair <QPoint, int> current(start, 0);
    queue.push_back(current);

    while (not queue.empty()) {
        current = queue.front();
        queue.pop_front();
        if (current.first.x() < 0 or current.first.x() >= width) {
            continue;
        }
        if (current.first.y() < 0 or current.first.y() >= height) {
            continue;
        }
        if ((*array)[current.first.x()][current.first.y()] != EMPTY_CELL_WITHOUT_TOWER) {
            continue;
        }
        (*array)[current.first.x()][current.first.y()] = current.second;
        current.second++;
        int x = current.first.x();
        int y = current.first.y();
        current.first.setX(x + 1);
        queue.push_back(current);

        current.first.setX(x - 1);
        queue.push_back(current);

        current.first.setX(x);
        current.first.setY(y + 1);
        queue.push_back(current);

        current.first.setY(y - 1);
        queue.push_back(current);
    }
}



int MainWindow::makeWayOf(QPoint end, int ***array, int width, int height, 
                                                                QList <QPoint> * save) {
    if ((*array)[end.x()][end.y()] == EMPTY_CELL_WITHOUT_TOWER) {
        return -1;
    }
    QPair <QPoint, int> current(end, (*array)[end.x()][end.y()]);
    QList <QPoint> deque;
    deque.push_front(QPoint(current.first.y(), current.first.x()));
    while (current.second != 0) {
        if (current.first.x() + 1 < width) {
            if ((*array)[current.first.x() + 1][current.first.y()] == (current.second - 1)) {
                current.first.setX(current.first.x() + 1);
                current.second--;
                deque.push_front(QPoint(current.first.y(), current.first.x()));
                continue;
            }
        }
        if (current.first.x() - 1 >= 0) {
            if ((*array)[current.first.x() - 1][current.first.y()] == (current.second - 1)) {
                current.first.setX(current.first.x() - 1);
                current.second--;
                deque.push_front(QPoint(current.first.y(), current.first.x()));
                continue;
            }
        }
        if (current.first.y() + 1 < height) {
            if ((*array)[current.first.x()][current.first.y() + 1] == (current.second - 1)) {
                current.first.setY(current.first.y() + 1);
                current.second--;
                deque.push_front(QPoint(current.first.y(), current.first.x()));
                continue;
            }
        }
        if (current.first.y() - 1 >= 0) {
            if ((*array)[current.first.x()][current.first.y() - 1] == (current.second - 1)) {
                current.first.setY(current.first.y() - 1);
                current.second--;
                deque.push_front(QPoint(current.first.y(), current.first.x()));
                continue;
            }
        }
    }
    (*save) = deque;
    return 0;
}



void MainWindow::update_fields_traectory() {

    int **tmp = new int *[LineCount];
    for (int i=0; i<LineCount; i++) {
        tmp[i] = new int[FieldInLineCount];
    }

    for (int i=0; i < LineCount; i++) {
        for (int j=0; j < FieldInLineCount; j++) {
            tmp[i][j] = helping_fields[i][j];
        }
    }

    makeWaysArray(respawn_point, &tmp, LineCount, FieldInLineCount);
    makeWayOf(enemy_target, &tmp, LineCount, FieldInLineCount, traectory);

    for (int i=0; i < LineCount; i++) {
        for (int j=0; j < FieldInLineCount; j++) {
            if (helping_fields[i][j] != BUSY_CELL) {
                tmp[i][j] = BUSY_CELL;
                makeWaysArray(respawn_point, &tmp, LineCount, FieldInLineCount);
                if (tmp[enemy_target.x()][enemy_target.y()] == EMPTY_CELL_WITHOUT_TOWER) {
                    helping_fields[i][j] = EMPTY_CELL_WITHOUT_TOWER;
                }
                else {
                    helping_fields[i][j] = EMPTY_CELL_MAYBE_TOWER;
                }
                tmp[i][j] = EMPTY_CELL_WITHOUT_TOWER;
            }
        }
    }
    helping_fields[respawn_point.x()][respawn_point.y()] = EMPTY_CELL_WITHOUT_TOWER;
    helping_fields[enemy_target.x()][enemy_target.y()] = EMPTY_CELL_WITHOUT_TOWER;

    for (int i=0; i<LineCount; i++) {
        delete[] tmp[i];
    }
    delete[] tmp;
}


void MainWindow::spawnEnemy() {
    Enemy * enemy = new Enemy(*traectory);
    connect(enemy, &Enemy::killed, this, &MainWindow::counterEnemyMinus);
    connect(enemy, &Enemy::GameOver, this, &MainWindow::gameOver);
    enemy->setPos(0, 305);
    scene->addItem(enemy);
    mustBeSpawned -= 1;
    livedEnemyCount += 1;

    if (mustBeSpawned <= 0){
        spawnTimer->disconnect();
    }
}


void MainWindow::createEnemies(int numberOfEnemies) {
    mustBeSpawned += numberOfEnemies;
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnEnemy()));
    spawnTimer->start(1500);
}

void MainWindow::chooseField(QPoint choosed) {
    if (current != QPoint(-1, -1)) {
        // send signal to current to delete frame
        emit changeFrame();
        disconnect(this, &MainWindow::changeFrame, fields[current.y()][current.x()],
                                                         &AbstractField::changeFrame);
    }
    current = choosed;
    connect(this, &MainWindow::changeFrame, fields[current.y()][current.x()],
                                                         &AbstractField::changeFrame);

    // send signal to current to make frame
    emit changeFrame();
}

void MainWindow::makeTower(int towerType) {
    addTower(current.x(), current.y(), towerType);
}


void MainWindow::gameBegin() {
    is_rest = true;
    roundTimer->start(10000);
}

void MainWindow::beginRound() {
    is_rest = false;
    roundTimer->stop();
    createEnemies(10 * level);
}

void MainWindow::counterEnemyMinus() {
    livedEnemyCount--;
    if (livedEnemyCount == 0) {
        level++;
        gameBegin();
    }
}

void MainWindow::gameOver() {
    QThread::sleep(3);
    qApp->quit();
}

void MainWindow::makeAbout() {
    QMessageBox::information(this, "About", "It's coursework of Nyagin Anatoliy, group M8O-110B-20");
}

void MainWindow::makeInfo() {
    QMessageBox::information(this, "Information", "Это игра жанра Tower Defense.\n\
    Ваша задача не допустить вражеских юнитов к их цели - серединной клетке правой стороны\n\
    Вражеские юниты появляются на серединном поле с левой стороны. Вы можете ставить башни,\n\
    которые будут стрелять в вражеских юнитов. Нельзя ставить башни так, что путь юнитов\n\
    закрыт. В начале каждого раунда у вас есть 10 секунд, чтобы поставить башни. Каждый\n\
    следующий раунд начинается после уничтожения всех юнитов текущего раунда.\n\
    Чтобы поставить башню, сначала кликом выберите клетку, после нажмите на кнопку башни\n\
    на панели справа. Игра закончится поражением в случае, когда хотя бы один юнит\n\
    доберется до цели. Приятной игры!");
}


