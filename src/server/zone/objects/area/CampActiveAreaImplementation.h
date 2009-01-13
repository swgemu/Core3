#ifndef CAMPACTIVEAREAIMPLEMENTATION_H_
#define CAMPACTIVEAREAIMPLEMENTATION_H_

#include "../player/Player.h"
#include "../tangible/campkit/CampSite.h"

class CampActiveAreaImplementation: public CampActiveAreaServant {
	CampSite* campSite;
public:
	CampActiveAreaImplementation(float x, float y, float z, float range,
			CampSite* camp) :
		CampActiveAreaServant(x, y, z, range) {
		campSite = camp;
	}

	void onEnter(Player * player) {
		campSite->enterNotification(player);
	}

	void onExit(Player * player) {
		campSite->exitNotificaton(player);
	}
};

#endif /* CAMPACTIVEAREAIMPLEMENTATION_H_ */

