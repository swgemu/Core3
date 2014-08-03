
#ifndef RENAMEGUILDTASK_H_
#define RENAMEGUILDTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/guild/GuildManager.h"

class RenameGuildTask : public Task {
	ZoneServer* server;

	ManagedWeakReference<GuildObject*> guildObject;

	ManagedWeakReference<CreatureObject*> member;

public:
	RenameGuildTask(CreatureObject* creature, ZoneServer* zserv, GuildObject* guildObj) : Task() {
		guildObject = guildObj;

		server = zserv;

		member = creature;
	}

	void run() {
		ManagedReference<GuildObject*> guild = guildObject.get();

		if (guild == NULL || !guild->isRenamePending())
			return;

		Locker locker(guild);

		ManagedReference<CreatureObject*> player = member.get();
		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (player == NULL || guildManager == NULL) {
			guild->setRenamePending(false);
			return;
		}

		String newName = guild->getPendingNewName();
		String newAbbrev = guild->getPendingNewAbbrev();

		if (!guildManager->validateGuildName(player, newName, guild)) {
			guild->setRenamePending(false);
			return;
		}

		if (!guildManager->validateGuildAbbrev(player, newAbbrev, guild)) {
			guild->setRenamePending(false);
			return;
		}

		guildManager->renameGuild(guild, player, newName, newAbbrev);
	}
};


#endif /* RENAMEGUILDTASK_H_ */
