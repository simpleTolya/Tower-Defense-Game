#ifndef ENEMY_H
#define ENEMY_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPair>
#include <QList>
#include <QTimer>

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    static const int MAX_HEALTH = 30;
    static const int RIGHT_SIDE = 1;
    static const int LEFT_SIDE = 0;

public:
    Enemy(QList <QPoint> &traectory);
    virtual ~Enemy();

private:
	static constexpr const char * const EnemyLeftImagePath =
			":/imgs/resources/white ghost left.png";
	static constexpr const char * const EnemyRightImagePath =
			":/imgs/resources/white ghost right.png";
    QTimer *timer;
    QList <QPoint> traectory;
    int health;
    bool side;

signals:
    void killed();
    void GameOver();

public slots:
    void slotEnemyTimer();
    void hit(int damage);
};

#endif // ENEMY_H
