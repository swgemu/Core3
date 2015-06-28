/*
 * GuildMemberListSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERLISTSUICALLBACK_H_
#define GUILDMEMBERLISTSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberListSuiCallback : public SuiCallback {
public:
	GuildMemberListSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal())
			return;

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

		SuiListBox* listBox = cast<SuiListBox*>( suiBox);

		uint64 memberID = listBox->getMenuObjectID(index);

		ManagedReference<GuildObject*> guild = player->getGuildObject();
		if (guild == NULL)
			return;

		if (!guild->hasMember(player->getObjectID()) && !player->getPlayerObject()->isPrivileged()) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); //You do not have permission to perform that operation.
			return;
		}

		guildManager->sendGuildMemberOptionsTo(player, guild, memberID, guildTerminal);
	}
};

#endif /* GUILDMEMBERLISTSUICALLBACK_H_ */
