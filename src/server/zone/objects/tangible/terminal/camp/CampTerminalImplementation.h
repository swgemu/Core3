#ifndef CAMPTERMINALIMPLEMENTATION_H_
#define CAMPTERMINALIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../campkit/campsite/CampSite.h"

#include "../TerminalImplementation.h"

#include "../../../../packets.h"

class CampTerminalImplementation : public CampTerminalServant {
	CampSite* camp;

public:
	CampTerminalImplementation(CampSite* campSite, uint64 objid, float x, float z, float y) :
		CampTerminalServant(0x53A8E0B8, objid, UnicodeString("Camp Terminal"), "base_terminal", x, z, y, CAMP) {

		camp = campSite;
	}

	int useObject(Player* player) {
		return 0;
	}

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
		if (camp == NULL)
			return;

		if (camp->getOwner() != player || camp->isAbandoned())
			return;
		omr->addRadialParent(252, 3, "Camp Status");
		omr->addRadialParent(182, 3, "@camp:mnu_disband");

		omr->finish();
		player->sendMessage(omr);
	}

	CampSite* getCampSite() {
		return camp;
	}
};

#endif /*CAMPTERMINALIMPLEMENTATION_H_*/
