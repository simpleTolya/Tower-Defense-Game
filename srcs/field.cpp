#include <QPainter>
#include "headers/field.h"

Field::Field() :
    AbstractField()
{
	setPixmap(QPixmap(DefaultFieldImagePath));
}


QRectF Field::boundingRect() const {
    return QRectF(0, 0, FIELD_WIDTH, FIELD_HEIGHT);
}


void Field::changeFrame() {
    if (hadFrame) {
		setPixmap(QPixmap(DefaultFieldImagePath));
    }
    else {
		setPixmap(QPixmap(ChoosedFieldImagePath));
    }
    hadFrame = !hadFrame;
}
