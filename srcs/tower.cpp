#include <typeinfo>
#include "headers/tower.h"
#include "headers/enemy.h"
#include "headers/bullet.h"

Tower::Tower() :
    AbstractField()
{
	rateOfFire = 500;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Tower::slotTowerTimer);
    timer->start(rateOfFire);

    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) << QPoint(2,3)
               << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // scale points
    int SCALE_FACTOR = 70;
    for (size_t i = 0, n = points.size(); i < n; i++){
        points[i] *= SCALE_FACTOR;
    }

    // create the QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(QPolygonF(points), this);
    attack_area->setPen(QPen(Qt::DotLine));

    QPointF poly_center(1.5, 1.5);
    poly_center *= SCALE_FACTOR;
    poly_center = mapToScene(poly_center);;
    QPointF tower_center(x() + 35, y() + 35);
    QLineF ln(poly_center, tower_center);
    attack_area->setPos(x()+ln.dx(), y()+ln.dy());

}

Tower::~Tower() {
    delete timer;
    delete attack_area;
}

double Tower::distanceTo(QGraphicsItem *item) {
    QLineF ln(this->pos(), item->pos());
    return ln.length();
}

void Tower::slotTowerTimer() {

    QList<QGraphicsItem *> foundItems = attack_area->collidingItems();

    foreach (QGraphicsItem *item, foundItems) {
        if (item != this and typeid((*item)) == typeid(Enemy)) {
            if ((item) and (distanceTo(item) < 300)) {
                emit Tower::fire(this->pos() + QPointF(35, 35), dynamic_cast<Enemy *>(item), damage, bulletImage);
                break;
            }
        }
    }
}


