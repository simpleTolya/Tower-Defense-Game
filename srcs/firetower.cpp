#include "headers/firetower.h"

FireTower::FireTower() :
    Tower()
{
    damage = 5;
    rateOfFire = 1000;
	setPixmap(QPixmap(TowerImagePath));
	bulletImage = QPixmap(BulletImagePath);
}
