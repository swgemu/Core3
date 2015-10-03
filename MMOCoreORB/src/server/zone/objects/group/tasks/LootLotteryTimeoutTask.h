/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOOTLOTTERYTIMEOUTTASKTASK_H_
#define LOOTLOTTERYTIMEOUTTASKTASK_H_

#include "server/zone/objects/player/sessions/LootLotterySession.h"

namespace server {
namespace zone {
namespace objects {
namespace group {
namespace tasks {

class LootLotteryTimeoutTask : public Task {

	ManagedReference<LootLotterySession*> session;

public:
	LootLotteryTimeoutTask(LootLotterySession* ses) : Task() {
		session = ses;
	}

	void run() {
		if (session != NULL)
			session->doLotteryDraw();
	}

};

} // namespace tasks
} // namespace group
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::group::tasks;

#endif /* LOOTLOTTERYTIMEOUTTASK_H_ */
