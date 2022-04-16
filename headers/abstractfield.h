#ifndef ABSTRACTFIELD_H
#define ABSTRACTFIELD_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class AbstractField : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    static const int FIELD_WIDTH = 70;
    static const int FIELD_HEIGHT = 70;

public:
    AbstractField();
    virtual ~AbstractField();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    bool hadFrame;

public slots:
    virtual void changeFrame();

signals:
    void clicked(QPoint);
};

#endif // ABSTRACTFIELD_H
