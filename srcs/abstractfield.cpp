
#include <iostream>
#include "headers/abstractfield.h"

AbstractField::AbstractField() :
   QObject(), QGraphicsPixmapItem()
{
    hadFrame = false;

}

AbstractField::~AbstractField() {}

void AbstractField::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    QPoint point(this->x() / AbstractField::FIELD_WIDTH, this->y() / AbstractField::FIELD_HEIGHT);
    emit clicked(point);
}

void AbstractField::changeFrame() {

}
