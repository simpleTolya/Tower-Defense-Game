#include "headers/firetowerbutton.h"

FireTowerButton::FireTowerButton() :
    TowerButton()
{
	setPixmap(QPixmap(ImagePath));
    towerButtonType = Tower::FIRE_TOWER_TYPE;
}
