#ifndef TOWER_H
#define TOWER_H

#include "abstractfield.h"
#include <QTimer>
#include <QGraphicsScene>
#include "enemy.h"

class Tower : public AbstractField
{
    Q_OBJECT
public:
    static const int FIRE_TOWER_TYPE = 1;
    static const int EARTH_TOWER_TYPE = 2;
    static const int ICE_TOWER_TYPE = 3;

protected:
    int damage;
    int rateOfFire;
    QGraphicsPolygonItem *attack_area;
    QTimer *timer;
    QPixmap bulletImage;

    double distanceTo(QGraphicsItem *item);

public slots:
    void slotTowerTimer();

signals:
    void fire(QPointF begin, Enemy * end, int, QPixmap &);

public:
    Tower();
    virtual ~Tower();
};

#endif // TOWER_H
