/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNCONSENTCOMMAND_H_
#define UNCONSENTCOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "QueueCommand.h"

class UnconsentCommand : public QueueCommand {
public:

	UnconsentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static void unconscent(CreatureObject* player, CreatureObject* targetPlayer) {
		String name = targetPlayer->getFirstName().toLowerCase();

		PlayerObject* ghost = player->getPlayerObject();
		ghost->removeFromConsentList(name);

		StringIdChatParameter stringId("base_player", "prose_unconsent"); //You revoke your consent from %TO.
		stringId.setTO(name);
		player->sendSystemMessage(stringId);

		StringIdChatParameter stringId2("base_player", "prose_lost_consent"); //%TO no longer consents you.
		stringId2.setTO(player->getFirstName());
		targetPlayer->sendSystemMessage(stringId2);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		if (ghost->getConsentListSize() <= 0) {
			creature->sendSystemMessage("@error_message:consent_to_empty"); //You have not granted consent to anyone.
			return GENERALERROR;
		}

		uint64 targetID = creature->getTargetID();

		if (arguments.isEmpty() && targetID == 0) {
			creature->sendSystemMessage("@error_message:syntax_unconsent"); //syntax: /unconsent {optionally, use commas to seperate several player names}
			return GENERALERROR;
		}

		if (!arguments.isEmpty()) {
			StringTokenizer tokenizer(arguments.toString());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String name = "";
				tokenizer.getStringToken(name);
				name = name.toLowerCase();

				PlayerManager* playerManager = server->getPlayerManager();
				bool validName = playerManager->existsName(name);

				if (!validName) {
					creature->sendSystemMessage("@ui_cmnty:friend_location_failed_noname"); //No player with that name exists.
					continue;
				} else if (!ghost->hasInConsentList(name)) {
					creature->sendSystemMessage("That player isn't on your consent list.");
					continue;
				} else {
					CreatureObject* targetPlayer = playerManager->getPlayer(name);

					if (targetPlayer == NULL)
						continue;

					unconscent(creature, targetPlayer);
				}
			}
		} else {
			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(targetID);
			CreatureObject* playerTarget = cast<CreatureObject*>( object.get());

			if (playerTarget == NULL || !playerTarget->isPlayerCreature() || playerTarget == creature)
				return INVALIDTARGET;

			unconscent(creature, playerTarget);
		}

		return SUCCESS;
	}

};

#endif //UNCONSENTCOMMAND_H_
