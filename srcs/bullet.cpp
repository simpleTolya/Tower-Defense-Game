
#include <math.h>
#include <qmath.h>
#include "headers/bullet.h"

qreal normalizeAngle(qreal angle)
{
    while (angle < 0) {
        angle += 2 * M_PI;
    }
    while (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}

Bullet::Bullet(QPointF start, Enemy * end, int _damage, QPixmap & bulletImage)
    : QObject(), QGraphicsPixmapItem()
{
    setPixmap(bulletImage);
    damage = _damage;
    target = end;
    targetKilled = false;

    connect(target, &Enemy::killed, this, &Bullet::flagTargetKilled);
    this->setRotation(0);
    this->setPos(start);

    QLineF lineToTarget(start, end->pos() + QPointF(10, 10));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = 2*M_PI - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

    if (angleToTarget >= 0 && angleToTarget < M_PI) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /M_PI);
    } else if (angleToTarget <= 2*M_PI && angleToTarget > M_PI) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - 2*M_PI )* (-180)/M_PI);
    }

    timerBullet = new QTimer();

    connect(timerBullet, &QTimer::timeout, this, &Bullet::slotTimerBullet);
    timerBullet->start(10);
}

Bullet::~Bullet()
{
    delete timerBullet;
}

void Bullet::slotTimerBullet()
{
    if (targetKilled) {
        delete this;
    }
    else {
        rotateToPoint(target->pos() + QPointF(10, 10));

        // move enemy forward at current angle
        int STEP_SIZE = 2;
        double theta = rotation(); // degrees

        double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
        double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

        setPos(x() + dx, y() + dy);

        double delta_x = x() - target->x() - 10;
        double delta_y = y() - target->y() - 10;
        if ((delta_x < 5) and (delta_x > -5) and (delta_x < 5) and (delta_y > -5)) {
            target->hit(damage);
            this->deleteLater();
        }

        if(this->x() < 0) {
            this->deleteLater();
        }
        if(this->x() > 1050) {
            this->deleteLater();
        }

        if(this->y() < 0) {
            this->deleteLater();
        }
        if(this->y() > 490) {
            this->deleteLater();
        }
    }
}

void Bullet::rotateToPoint(QPointF p) {
    QLineF ln(pos(), p);
    setRotation(-1 * ln.angle());
}

void Bullet::flagTargetKilled() {
    targetKilled = true;
}

