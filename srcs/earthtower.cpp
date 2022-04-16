#include "headers/earthtower.h"

EarthTower::EarthTower() :
    Tower()
{
    damage = 5;
    rateOfFire = 1000;
	setPixmap(QPixmap(TowerImagePath));
	bulletImage = QPixmap(BulletImagePath);
}
