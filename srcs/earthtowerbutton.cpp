#include "headers/earthtowerbutton.h"

EarthTowerButton::EarthTowerButton() :
    TowerButton()
{
	setPixmap(QPixmap(ImagePath));
    towerButtonType = Tower::EARTH_TOWER_TYPE;
}
