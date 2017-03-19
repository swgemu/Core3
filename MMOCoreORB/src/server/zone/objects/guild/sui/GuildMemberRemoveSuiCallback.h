/*
 * GuildMemberRemoveSuiCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERREMOVESUICALLBACK_H_
#define GUILDMEMBERREMOVESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberRemoveSuiCallback : public SuiCallback {
public:
	GuildMemberRemoveSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {

		bool cancelPressed = (eventIndex == 1);
		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* target = cast<CreatureObject*>( obj.get());

		guildManager->kickMember(player, target);
	}
};

#endif /* GUILDMEMBERREMOVESUICALLBACK_H_ */
