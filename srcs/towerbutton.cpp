#include "headers/towerbutton.h"

TowerButton::TowerButton() :
    QGraphicsPixmapItem()
{

}


void TowerButton::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Q_UNUSED(event);
    emit clicked(towerButtonType);
}
