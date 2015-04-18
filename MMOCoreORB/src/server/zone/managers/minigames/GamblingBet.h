/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GAMBLINGBET_H_
#define GAMBLINGBET_H_


#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace managers {
namespace minigames {

class GamblingBet {
	ManagedReference<CreatureObject*> player;
	int amount;
	String target;

public:
	GamblingBet(CreatureObject* pl, int bet, String betTarget) {
		player = pl;
		amount = bet;
		target = betTarget;
	}

	GamblingBet(CreatureObject* pl, int bet) {
		player = pl;
		amount = bet;
		target = "slot";
	}

	int getAmount() {
		return amount;
	}

	String getTarget() {
		return target;
	}

	CreatureObject* getPlayer() {
		return player;
	}

};

}
}
}
}


#endif




