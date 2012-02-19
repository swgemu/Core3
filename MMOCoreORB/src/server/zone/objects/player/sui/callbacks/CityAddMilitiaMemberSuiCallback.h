/*
 * CityAddMilitiaMemberSuiCallback.h
 *
 *  Created on: Feb 19, 2012
 *      Author: swgemu
 */

#ifndef CITYADDMILITIAMEMBERSUICALLBACK_H_
#define CITYADDMILITIAMEMBERSUICALLBACK_H_

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

class CityAddMilitiaMemberSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityAddMilitiaMemberSuiCallback(ZoneServer* server, CityRegion* city)
		: SuiCallback(server) {

		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		if (!suiBox->isInputBox() || player == NULL || cancelPressed || args->size() <= 0) {
			return;
		}

		String playerName = args->get(0).toString();

		CityManager* cityManager = cityRegion->getZone()->getCityManager();
		cityManager->addMilitiaMember(city, player, playerName);
	}
};

#endif /* CITYADDMILITIAMEMBERSUICALLBACK_H_ */
