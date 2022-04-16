#ifndef BULLET_H
#define BULLET_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>
#include "enemy.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QPointF start, Enemy * end, int _damage, QPixmap &);
    ~Bullet();

public slots:

private:
    void rotateToPoint(QPointF p);

private:
    QTimer *timerBullet;
    Enemy * target;
    int damage;
    bool targetKilled;

private slots:
    void flagTargetKilled();
    void slotTimerBullet();
};

#endif // BULLET_H
