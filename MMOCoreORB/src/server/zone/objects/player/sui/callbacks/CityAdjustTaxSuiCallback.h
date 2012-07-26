/*
 * CityAdjustTaxSuiCallback.h
 *
 *  Created on: Feb 19, 2012
 *      Author: swgemu
 */

#ifndef CITYADJUSTTAXSUICALLBACK_H_
#define CITYADJUSTTAXSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "../listbox/SuiListBox.h"

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

class CityAdjustTaxSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityAdjustTaxSuiCallback(ZoneServer* server, CityRegion* city)
		: SuiCallback(server) {

		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL || !suiBox->isListBox() || player == NULL || cancelPressed || args->size() <= 0) {
			return;
		}

		SuiListBox* listbox = cast<SuiListBox*>(suiBox);

		int idx = Integer::valueOf(args->get(0).toString());

		if (idx > listbox->getMenuSize() - 1 || idx < 0)
			return;

		int taxSelected = listbox->getMenuObjectID(idx);

		CityManager* cityManager = server->getCityManager();
		cityManager->promptSetTax(city, player, taxSelected, listbox->getUsingObject().get());
	}
};

#endif /* CITYADJUSTTAXSUICALLBACK_H_ */
