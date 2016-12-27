/*
 * CityRemoveMilitiaMemberSuiCallback.h
 *
 *  Created on: Feb 19, 2012
 *      Author: swgemu
 */

#ifndef CITYREMOVEMILITIAMEMBERSUICALLBACK_H_
#define CITYREMOVEMILITIAMEMBERSUICALLBACK_H_

#include "engine/engine.h"
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

class CityRemoveMilitiaMemberSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityRemoveMilitiaMemberSuiCallback(ZoneServer* server, CityRegion* city) : SuiCallback(server) {
		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CityRemoveMilitiaSession*> session = player->getActiveSession(SessionFacadeType::CITYMILITIA).castTo<CityRemoveMilitiaSession*>();

		if (session == NULL)
			return;

		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL || cancelPressed) {
			session->cancelSession();
			return;
		}

		CityManager* cityManager = server->getCityManager();
		cityManager->removeMilitiaMember(city, player, session->getMilitiaID());

		session->cancelSession();
	}
};

#endif /* CITYREMOVEMILITIAMEMBERSUICALLBACK_H_ */
