/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONSENTCOMMAND_H_
#define CONSENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class ConsentCommand : public QueueCommand {
public:

	ConsentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static void consent(CreatureObject* player, CreatureObject* targetPlayer) {
		String name = targetPlayer->getFirstName().toLowerCase();

		PlayerObject* ghost = player->getPlayerObject();
		ghost->addToConsentList(name);

		StringIdChatParameter stringId("base_player", "prose_consent"); //You give your consent to %TO.
		stringId.setTO(name);
		player->sendSystemMessage(stringId);

		StringIdChatParameter stringId2("base_player", "prose_got_consent"); // %TO consents you.
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

		if (ghost->getConsentListSize() >= 20) {
			creature->sendSystemMessage("You have too many players on your consent list.");
			return GENERALERROR;
		}

		uint64 targetID = creature->getTargetID();

		if (arguments.isEmpty() && targetID == 0) {
			creature->sendSystemMessage("To give consent, you must either specify the player name or target that player and use the command.");
			return GENERALERROR;
		}

		if (!arguments.isEmpty()) {
			StringTokenizer tokenizer(arguments.toString());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String name = "";
				tokenizer.getStringToken(name);
				name = name.toLowerCase();

				if (ghost->hasInConsentList(name)) {
					creature->sendSystemMessage("You already gave that player your consent.");
					return GENERALERROR;
				}

				PlayerManager* playerManager = server->getPlayerManager();
				bool validName = playerManager->existsName(name);

				if (!validName) {
					creature->sendSystemMessage("@ui_cmnty:friend_location_failed_noname"); //No player with that name exists.
					return GENERALERROR;
				} else if (creature->getFirstName().toLowerCase() == name) {
					creature->sendSystemMessage("You cannot give consent to yourself!");
					return INVALIDTARGET;
				} else {
					CreatureObject* targetPlayer = playerManager->getPlayer(name);

					if (targetPlayer == NULL)
						return INVALIDTARGET;

					consent(creature, targetPlayer);
				}
			}
		} else {
			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(targetID);
			CreatureObject* playerTarget = cast<CreatureObject*>( object.get());

			if (playerTarget == NULL || !playerTarget->isPlayerCreature() || playerTarget == creature) {
				return INVALIDTARGET;
			}

			if (ghost->hasInConsentList(playerTarget->getFirstName().toLowerCase())) {
				creature->sendSystemMessage("You already gave that player your consent.");
				return GENERALERROR;
			}

			consent(creature, playerTarget);
		}

		return SUCCESS;
	}

};

#endif //CONSENTCOMMAND_H_
