/*
 * CitySetTaxSuiCallback.h
 *
 *  Created on: Feb 19, 2012
 *      Author: swgemu
 */

#ifndef CITYSETTAXSUICALLBACK_H_
#define CITYSETTAXSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
namespace region {
	class CityRegion;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::region;

class CitySetTaxSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;
	int taxSelected;

public:
	CitySetTaxSuiCallback(ZoneServer* server, CityRegion* city, int tax)
		: SuiCallback(server) {

		cityRegion = city;
		taxSelected = tax;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL || !suiBox->isInputBox() || player == NULL || cancelPressed || args->size() <= 0) {
			return;
		}

		int value = Integer::valueOf(args->get(0).toString());

		CityManager* cityManager = server->getCityManager();
		cityManager->setTax(city, player, taxSelected, value);
	}
};

#endif /* CITYSETTAXSUICALLBACK_H_ */
