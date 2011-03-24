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
	GuildMemberPermissionsResponseSuiCallback(ZoneProcessServer* server)
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

		uint64 memberID = listBox->getMenuObjectID(index);

		ManagedReference<GuildManager*> guildManager = server->getZoneServer()->getGuildManager();

		if (guildManager == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = (Terminal*) obj.get();

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = (GuildTerminal*) terminal;

		ManagedReference<GuildObject*> guild = guildTerminal->getGuildObject();

		if (guild == NULL)
			return;

		guildManager->toggleGuildPermission(player, memberID, index, guildTerminal);
	}
};

#endif /* GUILDMEMBERPERMISSIONSRESPONSESUICALLBACK_H_ */
