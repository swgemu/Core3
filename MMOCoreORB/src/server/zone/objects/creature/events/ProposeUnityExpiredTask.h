/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PROPOSEUNITYEXPIREDTASK_H_
#define PROPOSEUNITYEXPIREDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/ProposeUnitySession.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class ProposeUnityExpiredTask : public Task {

	ManagedReference<CreatureObject*> player;

public:
	ProposeUnityExpiredTask(CreatureObject* player) : Task() {
		this->player = player;
	}

	void run() {

		if( player == NULL )
			return;

		Locker locker(player);
		player->removePendingTask("propose_unity");

		ManagedReference<ProposeUnitySession*> proposeUnitySession = player->getActiveSession(SessionFacadeType::PROPOSEUNITY).castTo<ProposeUnitySession*>();
		if(proposeUnitySession != NULL) {

			if( player->getObjectID() == proposeUnitySession->getAskingPlayer() ){
				player->sendSystemMessage("@unity:expire_player"); // "The unity proposal you extended has expired."
			}
			else{
				player->sendSystemMessage("@unity:expire_target"); // "The unity proposal extended to you has expired."
			}
			player->dropActiveSession(SessionFacadeType::PROPOSEUNITY);
		}
	}
};

} // events
} // creature
} // objects
} // zone
} // server

using namespace server::zone::objects::creature::events;

#endif /*PROPOSEUNITYEXPIREDTASK_H_*/
