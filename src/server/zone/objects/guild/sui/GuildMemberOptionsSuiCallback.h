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
	GuildMemberOptionsSuiCallback(ZoneProcessServer* server)
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

		ManagedReference<SceneObject*> playObj = server->getZoneServer()->getObject(memberID);

		if (playObj == NULL || !playObj->isPlayerCreature())
			return;

		PlayerCreature* target = (PlayerCreature*) playObj.get();

		//Guild Leader doesn't have the set allegiance option, so if this player is the guild leader, then we need to increment the index by 1!
		if (guild->isGuildLeader(player))
			++index;

		switch (index) {
		case 0: //Set Allegiance
			guildManager->setAllegianceTo(player, memberID, guildTerminal);
			break;
		case 1: //Kick
			guildManager->sendGuildKickPromptTo(player, target);
			break;
		case 2: //Set Title
			guildManager->sendGuildSetTitleTo(player, target);
			break;
		case 3: //Change Permissions
			guildManager->sendMemberPermissionsTo(player, memberID, guildTerminal);
			break;
		default:
			return;
		}
	}
};

#endif /* GUILDMEMBEROPTIONSSUICALLBACK_H_ */
