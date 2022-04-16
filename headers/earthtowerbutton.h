#ifndef EARTHTOWERBUTTON_H
#define EARTHTOWERBUTTON_H

#include "towerbutton.h"

class EarthTowerButton : public TowerButton
{
private:
	static constexpr const char * const ImagePath =
			":/imgs/resources/towerButton1.jpg";
public:
    EarthTowerButton();
};

#endif // EARTHTOWERBUTTON_H
