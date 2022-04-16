#ifndef FIRETOWERBUTTON_H
#define FIRETOWERBUTTON_H

#include "towerbutton.h"

class FireTowerButton : public TowerButton
{
private:
	static constexpr const char * const ImagePath =
			":/imgs/resources/towerButton2.jpg";
public:
    FireTowerButton();
};

#endif // FIRETOWERBUTTON_H
