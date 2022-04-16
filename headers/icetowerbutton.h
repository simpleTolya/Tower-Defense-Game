#ifndef ICETOWERBUTTON_H
#define ICETOWERBUTTON_H


#include "towerbutton.h"

class IceTowerButton : public TowerButton
{
private:
	static constexpr const char * const ImagePath =
			":/imgs/resources/towerButton3.jpg";
public:
    IceTowerButton();
};
#endif // ICETOWERBUTTON_H
