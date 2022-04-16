#include "headers/icetowerbutton.h"

IceTowerButton::IceTowerButton() :
    TowerButton()
{
	setPixmap(QPixmap(ImagePath));
    towerButtonType = Tower::ICE_TOWER_TYPE;
}
