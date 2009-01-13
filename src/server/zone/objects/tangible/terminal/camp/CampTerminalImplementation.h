#ifndef CAMPTERMINALIMPLEMENTATION_H_
#define CAMPTERMINALIMPLEMENTATION_H_

#include "../../../player/Player.h"
#include "../../campkit/CampSite.h"

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
		if (camp == NULL && (camp->getOwner() != player || camp->isAbandoned()))
			return;

		omr->addRadialItem(0, 204, 3, "@camp:mnu_disband");

		omr->finish();
		player->sendMessage(omr);
	}

	CampSite* getCampSite() {
		return camp;
	}
};

#endif /*GUILDTERMINALIMPLEMENTATION_H_*/
