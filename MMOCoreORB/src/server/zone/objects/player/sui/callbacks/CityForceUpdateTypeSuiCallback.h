
#ifndef CITYFORCEUPDATETYPESUICALLBACK_H_
#define CITYFORCEUPDATETYPESUICALLBACK_H_

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

class CityForceUpdateTypeSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityForceUpdateTypeSuiCallback(ZoneServer* server, CityRegion* city) : SuiCallback(server) {
		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		if (!suiBox->isMessageBox() || player == NULL) {
			return;
		}

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		if (!ghost->isPrivileged())
			return;

		Locker clocker(city, player);

		StringIdChatParameter params;
		params.setTO(city->getRegionName());

		CityManager* cityManager = server->getCityManager();

		if (cancelPressed) {
			params.setStringId("city/city", "force_city_update"); // Forcing a city update for city %TO.
			cityManager->processCityUpdate(city);
		} else {
			params.setStringId("city/city", "force_city_election"); // Forcing a city update for city %TO.
			cityManager->updateCityVoting(city,true);
		}

		player->sendSystemMessage(params);
	}
};

#endif /* CITYFORCEUPDATETYPESUICALLBACK_H_ */
