/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMBLINGSLOTEVENT_H_
#define GAMBLINGSLOTEVENT_H_

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/minigames/gambling/GamblingManager.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {
namespace events {

class GamblingSlotEvent : public Task {
	ManagedWeakReference<GamblingManager*> gamblingManager;
	ManagedReference<CreatureObject*> player;
	ManagedReference<GamblingTerminal*> terminal;
	int rollNum;
	int rollResults[3] = { 0, 0, 0 };

public:
	GamblingSlotEvent(GamblingManager* gamb, CreatureObject* play, GamblingTerminal* term) : Task() {
		gamblingManager = gamb;
		player = play;
		rollNum = 0;
		terminal = term;
	}

	void run() {
		ManagedReference<GamblingManager*> strongRef = gamblingManager.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		int rollResult = 0;

		if (System::random(100) > 50)
			rollResult = strongRef->getRandomSlotRoll();

		rollResults[rollNum] = rollResult;

		String msg = "Slot Machine Pay Line\n";

		for (int i = 0; i <= rollNum; i++)
			msg += "| " + String::valueOf(rollResults[i]) + " | ";

		for (int i = rollNum + 1; i <= 3; i++)
			msg += "|Rolling...| ";

		msg += "--";

		player->sendSystemMessage(msg);

		if (rollNum == 2) {
			int slotRoll = (rollResults[0] * 100) + (rollResults[1] * 10) + rollResults[2];
			strongRef->handleSlotResults(player, terminal, slotRoll);
		} else {
			rollNum++;
			reschedule(3000);
		}
	}

};

}
}
}
}
}

using namespace server::zone::managers::minigames::events;

#endif /* GAMBLINGSLOTEVENT_H_ */
