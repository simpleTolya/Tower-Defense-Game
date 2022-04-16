#ifndef TOWERBUTTON_H
#define TOWERBUTTON_H

#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QObject>
#include "tower.h"

class TowerButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TowerButton();

signals:
  void clicked(int );

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event);

  int towerButtonType;
};

#endif // TOWERBUTTON_H
