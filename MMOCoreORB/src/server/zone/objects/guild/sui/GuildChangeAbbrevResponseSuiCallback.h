
#ifndef GUILDCHANGEABBREVRESPONSESUICALLBACK_H_
#define GUILDCHANGEABBREVRESPONSESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildChangeAbbrevResponseSuiCallback : public SuiCallback {
	ManagedWeakReference<GuildObject*> guildObject;

public:
	GuildChangeAbbrevResponseSuiCallback(ZoneServer* server, GuildObject* guild)
		: SuiCallback(server) {

		guildObject = guild;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		uint64 playerID = player->getObjectID();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();
		ManagedReference<GuildObject*> guild = guildObject.get();
		if (guild == NULL || guildManager == NULL)
			return;

		Locker glocker(guild, player);

		//If the new name isn't set, then exit.
		if (guild->getPendingNewName().isEmpty())
			return;

		//After this point, we have to resetRename() anywhere we return prematurely

		if (!guild->hasNamePermission(playerID) && !player->getPlayerObject()->isPrivileged()) {
			guild->resetRename();
			player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
			return;
		}

		if (!suiBox->isInputBox() || cancelPressed) {
			guild->resetRename();
			return;
		}

		if (args->size() < 1) {
			guild->resetRename();
			return;
		}

		String guildAbbrev = args->get(0).toString();

		if (guildManager->validateGuildAbbrev(player, guildAbbrev, guild)) {
			guild->setPendingNewAbbrev(guildAbbrev);
			guildManager->setupGuildRename(player, guild);
			return;
		}

		//Resend the create abbrev box.
		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	}
};


#endif /* GUILDCHANGEABBREVRESPONSESUICALLBACK_H_ */
