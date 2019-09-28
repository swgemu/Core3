
#ifndef RENAMEGUILDTASK_H_
#define RENAMEGUILDTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/guild/GuildManager.h"

class RenameGuildTask : public Task {
	ZoneServer* server;

	ManagedWeakReference<GuildObject*> guildObject;

public:
	RenameGuildTask(ZoneServer* zserv, GuildObject* guildObj) : Task() {
		guildObject = guildObj;

		server = zserv;
	}

	void run() {
		ManagedReference<GuildObject*> guild = guildObject.get();

		if (guild == nullptr || !guild->isRenamePending())
			return;

		Locker locker(guild);

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();
		if (guildManager == nullptr) {
			guild->resetRename();
			return;
		}

		guildManager->renameGuild(guild);
	}
};


#endif /* RENAMEGUILDTASK_H_ */
