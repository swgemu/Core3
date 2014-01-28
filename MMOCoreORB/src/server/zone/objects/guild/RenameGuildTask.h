
#ifndef RENAMEGUILDTASK_H_
#define RENAMEGUILDTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"

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

		ManagedReference<CreatureObject*> player = member.get();
		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (player == NULL || guildManager == NULL)
			return;

		String newName = guild->getPendingNewName();
		String newAbbrev = guild->getPendingNewAbbrev();

		if (!guildManager->validateGuildRename(player, newName, guild)) {
			guild->setRenamePending(false);
			return;
		}

		if (!guildManager->validateGuildRenameAbbrev(player, newAbbrev, guild)) {
			guild->setRenamePending(false);
			return;
		}

		guildManager->renameGuild(guild, newName, newAbbrev);
	}
};


#endif /* RENAMEGUILDTASK_H_ */
