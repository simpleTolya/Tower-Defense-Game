#ifndef FIRETOWER_H
#define FIRETOWER_H

#include "tower.h"

class FireTower : public Tower
{
private:
	static constexpr const char * const TowerImagePath =
			":/imgs/resources/tower2.jpg";
	static constexpr const char * const BulletImagePath =
			":/imgs/resources/fire.png";
public:
    FireTower();
};

#endif // FIRETOWER_H
