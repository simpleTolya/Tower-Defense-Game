#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include "abstractfield.h"



class Field : public AbstractField
{
    Q_OBJECT
private:
	static constexpr const char * const DefaultFieldImagePath =
			":/imgs/resources/trava3.jpg";
	static constexpr const char * const ChoosedFieldImagePath =
			":/imgs/resources/choosed_field.jpg";
public:
    Field();
    QRectF boundingRect() const;

signals:

public slots:
    void changeFrame();
};

#endif // FIELD_H
