/*
 * GuildTransferLotsSuiCallback.h
 *
 *  Created on: Oct 9, 2012
 *      Author: root
 */

#ifndef GUILDTRANSFERLOTSSUICALLBACK_H_
#define GUILDTRANSFERLOTSSUICALLBACK_H_
#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"

class GuildTransferLotsSuiCallback : public SuiCallback {
public:
	GuildTransferLotsSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox())
			return;

		if (cancelPressed)
			return;

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		ManagedReference<SceneObject*> usingObject = suiBox->getUsingObject();
		if (usingObject == NULL)
			return;

		Terminal* terminal = usingObject.castTo<Terminal*>();
		if (terminal == NULL || !terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = cast<GuildTerminal*>( terminal);
		if (guildTerminal == NULL)
			return;

		ManagedReference<BuildingObject*> buildingObject = cast<BuildingObject*>( guildTerminal->getParentRecursively(SceneObjectType::BUILDING).get().get());
		if (buildingObject == NULL)
			return;

		ManagedReference<CreatureObject*> owner = buildingObject->getOwnerCreatureObject();
		if (owner == NULL || !owner->isPlayerCreature())
			return;

		ManagedReference<PlayerObject*> ownerGhost = owner->getPlayerObject().get();
		ManagedReference<GuildObject*> guildObject = owner->getGuildObject().get();
		if (ownerGhost == NULL || guildObject == NULL)
			return;

		if (player->getPlayerObject()->getLotsRemaining() < 5) {
			player->sendSystemMessage("@guild:no_lots"); // You don't have enough lots free to take over the PA hall. You need to have 5 free lots.
			return;
		}

		if (guildObject->getGuildLeaderID() == player->getObjectID() && !ownerGhost->isOnline() && ownerGhost->getDaysSinceLastLogout() >= 28) {
			guildManager->transferGuildHall(player, usingObject);
		}

	}

};

#endif /* GUILDTRANSFERLOTSSUICALLBACK_H_ */
