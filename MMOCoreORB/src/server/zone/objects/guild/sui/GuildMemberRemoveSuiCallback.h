/*
 * GuildMemberRemoveSuiCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERREMOVESUICALLBACK_H_
#define GUILDMEMBERREMOVESUICALLBACK_H_


#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberRemoveSuiCallback : public SuiCallback {
public:
	GuildMemberRemoveSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* target = cast<CreatureObject*>( obj.get());

		guildManager->kickMember(player, target);
	}
};

#endif /* GUILDMEMBERREMOVESUICALLBACK_H_ */
