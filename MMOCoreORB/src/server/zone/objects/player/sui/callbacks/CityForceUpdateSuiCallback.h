
#ifndef CITYFORCEUPDATESUICALLBACK_H_
#define CITYFORCEUPDATESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/CityForceUpdateTypeSuiCallback.h"

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

class CityForceUpdateSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityForceUpdateSuiCallback(ZoneServer* server, CityRegion* city) : SuiCallback(server) {
		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		if (!suiBox->isMessageBox() || player == NULL || cancelPressed) {
			return;
		}

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		if (!ghost->isPrivileged())
			return;

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::CITY_ADMIN_CONFIRM_UPDATE_TYPE);
		box->setPromptTitle("@city/city:force_city_update_t"); // Force City Update
		box->setPromptText("@city/city:force_election_only"); // Do you only want to force an election?
		box->setCancelButton(true, "@no");
		box->setOkButton(true, "@yes");
		box->setCallback(new CityForceUpdateTypeSuiCallback(server, city) );

		ghost->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}
};

#endif /* CITYFORCEUPDATESUICALLBACK_H_ */
