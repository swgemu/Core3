/*
 * ListGuildsResponseSuiCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef LISTGUILDSRESPONSESUICALLBACK_H_
#define LISTGUILDSRESPONSESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/guild/GuildManager.h"

class ListGuildsResponseSuiCallback : public SuiCallback {
public:
	ListGuildsResponseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (!player->getPlayerObject()->isPrivileged())
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		uint64 guildObjectID = listBox->getMenuObjectID(index);

		ManagedReference<SceneObject*> obj = server->getObject(guildObjectID);

		if (obj == NULL || !obj->isGuildObject())
			return;

		GuildObject* guild = cast<GuildObject*>( obj.get());

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		guildManager->sendAdminGuildInfoTo(player, guild);
	}
};

#endif /* LISTGUILDSRESPONSESUICALLBACK_H_ */
