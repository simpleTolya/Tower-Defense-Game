#include "headers/enemy.h"

Enemy::Enemy(QList <QPoint> &_traectory) :
    QGraphicsPixmapItem()
{
	setPixmap(QPixmap(EnemyRightImagePath));
    side = RIGHT_SIDE;
    health = MAX_HEALTH;
    traectory = _traectory;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::slotEnemyTimer);
    timer->start(50);
}

Enemy::~Enemy() {
    delete timer;
}

void Enemy::slotEnemyTimer() {

    if (not traectory.isEmpty()) {
        QPointF next_point = traectory.first();
        next_point.setX(next_point.x()*70 + 25);
        next_point.setY(next_point.y()*70 + 25);
        double rasst_x = this->x() - next_point.x();
        double rasst_y = this->y() - next_point.y();
        if ((rasst_x < -0.001) or (rasst_x > 0.001)) {

            if (rasst_x < 0) {
                this->setPos(this->x() + 1, this->y());
                if (side != RIGHT_SIDE) {
					setPixmap(QPixmap(EnemyRightImagePath));
                    side = RIGHT_SIDE;
                }
            }
            if (rasst_x > 0) {
                this->setPos(this->x() - 1, this->y());
                if (side != LEFT_SIDE) {
					setPixmap(QPixmap(EnemyLeftImagePath));
                    side = LEFT_SIDE;
                }
            }
        }
        else if ((rasst_y < -0.001) or (rasst_y > 0.001)) {

            if (rasst_y < 0) {
                this->setPos(this->x(), this->y() + 1);
            }
            if (rasst_y > 0) {
                this->setPos(this->x(), this->y() - 1);
            }
        }
        else
            traectory.pop_front();
    } else {
         emit GameOver();
         this->deleteLater();
    }
}

void Enemy::hit(int damage) {
    health -= damage;
    if (health <= 0) {
        emit killed();
        delete this;
    }
}

