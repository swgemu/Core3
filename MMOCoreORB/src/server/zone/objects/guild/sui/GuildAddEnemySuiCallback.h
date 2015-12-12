/*
 * GuildAddEnemySuiCallback.h
 *
 *  Created on: Jun 7, 2012
 *      Author: chris.rush
 */

#ifndef GUILDADDENEMYSUICALLBACK_H_
#define GUILDADDENEMYSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class GuildAddEnemySuiCallback : public SuiCallback {
	ManagedWeakReference<GuildObject*> guildObject;

public:
	GuildAddEnemySuiCallback(ZoneServer* server, GuildObject* guild)
		: SuiCallback(server) {

		guildObject = guild;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || player == NULL || args->size() <= 0 || cancelPressed)
			return;

		SuiListBox* listbox = cast<SuiListBox*>(suiBox);

		int idx = Integer::valueOf(args->get(0).toString());

		if (idx >= listbox->getMenuSize() || idx < 0)
			return;

		uint64 oid = listbox->getMenuObjectID(idx);

		if (oid == 0) {
			server->getGuildManager()->promptAddNewEnemy(player, guildObject.get(), suiBox->getUsingObject().get());
		} else {
			server->getGuildManager()->toggleWarStatus(player, guildObject.get(), oid);
		}
	}
};

#endif /* GUILDADDENEMYSUICALLBACK_H_ */
