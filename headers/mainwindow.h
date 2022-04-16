#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QPoint>
#include <QPair>
#include "field.h"
#include "enemy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void changeFrame();
    void allEnemiesKilled();

private:
    static const int FieldInLineCount = 16;
    static const int LineCount = 9;

	static constexpr const char * const ButtonPanelImagePath =
			":/imgs/resources/trava2.jpg";
	static constexpr const char * const TopLeftAngleImagePath =
			":/imgs/resources/wall_ang1.jpg";
	static constexpr const char * const TopRightAngleImagePath =
			":/imgs/resources/wall_ang2.jpg";
	static constexpr const char * const DownLeftAngleImagePath =
			":/imgs/resources/wall_ang3.jpg";
	static constexpr const char * const DownRightAngleImagePath =
			":/imgs/resources/wall_ang4.jpg";
	static constexpr const char * const HorWallImagePath =
			":/imgs/resources/wall_hor.jpg";
	static constexpr const char * const VerWallImagePath =
			":/imgs/resources/wall_ver.jpg";
public slots:
    void fire(QPointF begin, Enemy * end, int damage, QPixmap &);
    void chooseField(QPoint);
    void spawnEnemy();
    void makeTower(int );
    void counterEnemyMinus();
    void beginRound();
    void gameBegin();
    void gameOver();
    void makeAbout();
    void makeInfo();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addTower(int column, int string, int towerType);
    void deleteTower(int column, int string);

private:
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    Ui::MainWindow *ui;
    QList <QPoint> *traectory;
    AbstractField * fields[LineCount][FieldInLineCount];
    QTimer * spawnTimer;
    QTimer * roundTimer;
    int mustBeSpawned;
    int livedEnemyCount;
    QPoint current;
    bool is_rest;
    int level;

private:
    static const int BUSY_CELL = 1000;
    static const int EMPTY_CELL_WITHOUT_TOWER = 1001;
    static const int EMPTY_CELL_MAYBE_TOWER = 1002;
    int helping_fields[LineCount][FieldInLineCount];

    void createEnemies(int numberOfEnemies);
    void update_fields_traectory();
    void makeWaysArray(QPoint start, int ***array, int width, int height);
    int makeWayOf(QPoint end, int ***array, int width, int height, QList <QPoint> * save);

    static const QPoint respawn_point;
    static const QPoint enemy_target;
};



#endif // MAINWINDOW_H



