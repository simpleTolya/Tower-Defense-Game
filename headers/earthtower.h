#ifndef EARTHTOWER_H
#define EARTHTOWER_H

#include "tower.h"

class EarthTower : public Tower
{
private:
	static constexpr const char * const TowerImagePath =
			":/imgs/resources/tower1.jpg";
	static constexpr const char * const BulletImagePath =
			":/imgs/resources/rock.png";
public:
    EarthTower();
};

#endif // EARTHTOWER_H
