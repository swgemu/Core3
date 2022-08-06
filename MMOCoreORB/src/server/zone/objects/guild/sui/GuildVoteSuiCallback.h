/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GUILDVOTESUICALLBACK_H_
#define GUILDVOTESUICALLBACK_H_


#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildVoteSuiCallback : public SuiCallback {
public:
	GuildVoteSuiCallback(ZoneServer* server)
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

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager == nullptr)
			return;

		ManagedReference<SceneObject*> sceneO = suiBox->getUsingObject().get();

		if (sceneO == nullptr || (!sceneO->isGuildTerminal() && !sceneO->isGuildManagementDroid())) {
			return;
		}

		ManagedReference<GuildObject*> guild = player->getGuildObject().get();

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		uint64 candidateID = listBox->getMenuObjectID(index);

		guildManager->castVote(guild, player, candidateID);
	}
};


#endif /* GUILDVOTESUICALLBACK_H_ */
