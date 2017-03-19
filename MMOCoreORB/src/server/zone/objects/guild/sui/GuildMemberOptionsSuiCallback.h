/*
 * GuildMemberOptionsSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBEROPTIONSSUICALLBACK_H_
#define GUILDMEMBEROPTIONSSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildMemberOptionsSuiCallback : public SuiCallback {
public:
	GuildMemberOptionsSuiCallback(ZoneServer* server)
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

		ManagedReference<SceneObject*> playObj = server->getObject(memberID);

		if (playObj == NULL || !playObj->isPlayerCreature())
			return;

		CreatureObject* target = cast<CreatureObject*>( playObj.get());

		switch (index) {
		case 0: //Set Title
			guildManager->sendGuildSetTitleTo(player, target);
			break;
		case 1: //Kick
			guildManager->sendGuildKickPromptTo(player, target);
			break;
		case 2: //Change Permissions
			guildManager->sendMemberPermissionsTo(player, memberID, guildTerminal);
			break;
		default:
			return;
		}
	}
};

#endif /* GUILDMEMBEROPTIONSSUICALLBACK_H_ */
