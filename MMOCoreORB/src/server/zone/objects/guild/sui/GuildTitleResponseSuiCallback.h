/*
 * GuildMemberTitleCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERTITLESUICALLBACK_H_
#define GUILDMEMBERTITLESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildTitleResponseSuiCallback : public SuiCallback {
public:
	GuildTitleResponseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		String title = args->get(0).toString();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL || !obj->isPlayerCreature())
			return;

		CreatureObject* target = cast<CreatureObject*>( obj.get());

		guildManager->setMemberTitle(player, target, title);
	}
};

#endif /* GUILDMEMBERTITLESUICALLBACK_H_ */
