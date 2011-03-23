/*
 * ListGuildsResponseCallback.h
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#ifndef LISTGUILDSRESPONSECALLBACK_H_
#define LISTGUILDSRESPONSECALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/guild/GuildManager.h"

class ListGuildsResponseCallback : public SuiCallback {
public:
	ListGuildsResponseCallback(ZoneProcessServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = (SuiListBox*) suiBox;

		uint64 guildObjectID = listBox->getMenuObjectID(index);

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(guildObjectID);

		if (obj == NULL || !obj->isGuildObject())
			return;

		GuildObject* guild = (GuildObject*) obj.get();

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		guildManager->sendGuildInformationTo(player, guild, NULL);
	}
};

#endif /* LISTGUILDSRESPONSECALLBACK_H_ */
