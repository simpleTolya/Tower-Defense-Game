#include "headers/icetower.h"

IceTower::IceTower() :
    Tower()
{
    damage = 5;
    rateOfFire = 1000;
	setPixmap(QPixmap(TowerImagePath));
	bulletImage = QPixmap(BulletImagePath);
}
