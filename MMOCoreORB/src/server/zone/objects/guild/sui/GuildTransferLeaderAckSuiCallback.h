/*
 * GuildTransferLeaderAckSuiCallback.h
 *
 *  Created on: Oct 8, 2012
 *      Author: root
 */

#ifndef GUILDTRANSFERLEADERACKSUICALLBACK_H_
#define GUILDTRANSFERLEADERACKSUICALLBACK_H_

#include "server/zone/managers/guild/GuildManager.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"

class GuildTransferLeaderAckSuiCallback : public SuiCallback {
public:
	GuildTransferLeaderAckSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* newLeader, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<SceneObject*> sceoTerminal = suiBox->getUsingObject().get();
		if (sceoTerminal == NULL || !sceoTerminal->isTerminal())
			return;

		Terminal* terminal = sceoTerminal.castTo<Terminal*>();
		if (!terminal->isGuildTerminal())
			return;

		GuildTerminal* guildTerminal = cast<GuildTerminal*>(terminal);
		if (guildTerminal == NULL)
			return;

		ManagedReference<BuildingObject*> buildingObject = guildTerminal->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();
		if (buildingObject == NULL)
			return;

		ManagedReference<CreatureObject*> owner = buildingObject->getOwnerCreatureObject();
		if (owner == NULL || !owner->isPlayerCreature()) {
			return;
		}

		ManagedReference<GuildObject*> guild = owner->getGuildObject().get();
		if (guild == NULL || !guild->isTransferPending())
			return;

		Locker clocker(guild, newLeader);

		if (guild->getGuildLeaderID() != owner->getObjectID() || guild != newLeader->getGuildObject().get()) {
			guild->setTransferPending(false);
			return;
		}

		if ( cancelPressed ) {
			guild->setTransferPending(false);
			owner->sendSystemMessage("@guild:ml_rejected"); // That player does not want to become guild leader
			return;
		}

		ManagedReference<GuildManager*> guildManager = server->getGuildManager();

		if ( guildManager != NULL ) {
			ManagedReference<CreatureObject*> newOwner = newLeader;

			Core::getTaskManager()->executeTask([=] () {
				// transfer structure to new leader
				if (guildManager->transferGuildHall(newOwner, sceoTerminal)) {
					// change leadership of guild
					guildManager->transferLeadership(newOwner, owner, false);
				}
			}, "TransferGuildLambda");
		}
	}
};

#endif /* GUILDTRANSFERLEADERACKSUICALLBACK_H_ */
