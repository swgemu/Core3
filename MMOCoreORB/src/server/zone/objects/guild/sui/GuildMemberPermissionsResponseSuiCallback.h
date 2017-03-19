/*
 * GuildMemberPermissionsResponseSuiCallback.h
 *
 *  Created on: Nov 5, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_
#define GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberPermissionsResponseSuiCallback : public SuiCallback {
public:
	GuildMemberPermissionsResponseSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		uint64 memberID = listBox->getMenuObjectID(index);

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		if (guild == NULL)
			return;

		guildManager->toggleGuildPermission(player, memberID, index, guildTerminal);
	}
};

#endif /* GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_ */
