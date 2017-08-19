
#ifndef GUILDUPDATEEVENT_H_
#define GUILDUPDATEEVENT_H_

#include "engine/engine.h"
#include "server/zone/objects/guild/GuildObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/guild/GuildManager.h"

namespace server {
namespace zone {
namespace objects {
namespace guild {

class GuildUpdateEvent : public Task {
	ZoneServer* server;

	ManagedWeakReference<GuildObject*> guildObject;

public:
	GuildUpdateEvent(GuildObject* guildObj, ZoneServer* zserv) : Task() {
		guildObject = guildObj;

		server = zserv;

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		if (server == NULL || server->isServerShuttingDown())
			return;

		ManagedReference<GuildObject*> guild = guildObject.get();

		if (guild == NULL)
			return;

		Locker locker(guild);

		if (server->isServerLoading()) {
			guild->rescheduleUpdateEvent(10000);
			return;
		}

		GuildManager* guildManager = server->getGuildManager();

		guildManager->processGuildUpdate(guild);
	}
};

}
}
}
}

using namespace server::zone::objects::guild;

#endif /* GUILDUPDATEEVENT_H_ */
