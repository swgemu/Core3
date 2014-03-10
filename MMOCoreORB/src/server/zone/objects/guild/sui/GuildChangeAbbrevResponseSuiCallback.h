
#ifndef GUILDCHANGEABBREVRESPONSESUICALLBACK_H_
#define GUILDCHANGEABBREVRESPONSESUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildChangeAbbrevResponseSuiCallback : public SuiCallback {
	ManagedWeakReference<GuildObject*> guildObject;

public:
	GuildChangeAbbrevResponseSuiCallback(ZoneServer* server, GuildObject* guild)
		: SuiCallback(server) {

		guildObject = guild;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		uint64 playerID = player->getObjectID();

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		ManagedReference<GuildObject*> guild = guildObject.get();

		Locker glocker(guild, player);

		//If a rename isn't pending, then exit.
		if (!guild->isRenamePending())
			return;

		if (!guild->hasNamePermission(playerID) && !player->getPlayerObject()->isPrivileged()) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
			return;
		}

		//After this point, we have to setRenamePending(false) anywhere we return, since they have to be renaming a guild at this point.

		if (!suiBox->isInputBox() || cancelPressed) {
			guild->setRenamePending(false);
			return;
		}

		if (args->size() < 1) {
			guild->setRenamePending(false);
			return;
		}

		String guildAbbrev = args->get(0).toString();

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL || !obj->isTerminal()) {
			guild->setRenamePending(false);
			return;
		}

		Terminal* terminal = cast<Terminal*>( obj.get());

		if (!terminal->isGuildTerminal()) {
			guild->setRenamePending(false);
			return;
		}

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);

		if (guildManager->validateGuildAbbrev(player, guildAbbrev, guild)) {
			guild->setPendingNewAbbrev(guildAbbrev);
			guildManager->scheduleGuildRename(player, guild);
			return;
		}

		//Resend the create abbrev box.
		player->getPlayerObject()->addSuiBox(suiBox);
		player->sendMessage(suiBox->generateMessage());
	}
};


#endif /* GUILDCHANGEABBREVRESPONSESUICALLBACK_H_ */
