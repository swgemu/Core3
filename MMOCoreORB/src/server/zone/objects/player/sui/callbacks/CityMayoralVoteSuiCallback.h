/*
 * CityMayoralVoteSuiCallback.h
 *
 *  Created on: Jun 7, 2012
 *      Author: chris.rush
 */

#ifndef CITYMAYORALVOTESUICALLBACK_H_
#define CITYMAYORALVOTESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

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

class CityMayoralVoteSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityMayoralVoteSuiCallback(ZoneServer* server, CityRegion* city)
		: SuiCallback(server) {

		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		if (!suiBox->isListBox() || player == NULL || args->size() <= 0 || cancelPressed)
			return;

		SuiListBox* listbox = cast<SuiListBox*>(suiBox);

		int idx = Integer::valueOf(args->get(0).toString());

		if (idx >= listbox->getMenuSize() || idx < 0)
			return;

		uint64 oid = listbox->getMenuObjectID(idx);

		Locker clocker(city, player);

		CityManager* cityManager = server->getCityManager();
		cityManager->castMayoralVote(city, player, oid);
	}
};

#endif /* CITYMAYORALVOTESUICALLBACK_H_ */
