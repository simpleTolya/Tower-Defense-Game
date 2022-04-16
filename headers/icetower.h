#ifndef ICETOWER_H
#define ICETOWER_H

#include "tower.h"

class IceTower : public Tower
{
private:
	static constexpr const char * const TowerImagePath =
			":/imgs/resources/tower3.jpg";
	static constexpr const char * const BulletImagePath =
			":/imgs/resources/ice.png";
public:
    IceTower();
};

#endif // ICETOWER_H
