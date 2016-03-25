
#ifndef GUILDADMININFOSUICALLBACK_H_
#define GUILDADMININFOSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class GuildAdminInfoSuiCallback : public SuiCallback {
	ManagedWeakReference<GuildObject*> guildObject;

public:
	GuildAdminInfoSuiCallback(ZoneServer* server, GuildObject* guild)
		: SuiCallback(server) {

		guildObject = guild;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		uint64 playerID = player->getObjectID();

		ManagedReference<GuildObject*> guild = guildObject.get();

		if (guild == NULL)
			return;

		if (!guild->hasNamePermission(playerID) && !player->getPlayerObject()->isPrivileged()) {
			player->sendSystemMessage("@guild:generic_fail_no_permission"); // You do not have permission to perform that operation.
			return;
		}

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if (guildManager != NULL) {
			guildManager->sendGuildChangeNameTo(player, guild);
		}
	}
};

#endif /* GUILDADMININFOSUICALLBACK_H_ */
