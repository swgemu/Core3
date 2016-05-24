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

	static void consent(CreatureObject* player, const String& name) {
		PlayerObject* ghost = player->getPlayerObject();
		ghost->addToConsentList(name);

		StringIdChatParameter stringId("base_player", "prose_consent"); //You give your consent to %TO.
		stringId.setTO(name);
		player->sendSystemMessage(stringId);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		//System::out << "entering ConsentCommand" << endl;
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		//System::out << "past initial checks ConsentCommand" << endl;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost != NULL && ghost->getConsentListSize() >= 20) {
			creature->sendSystemMessage("You have too many players on your consent list.");
			return GENERALERROR;
		}

		if (arguments.isEmpty() && !creature->getTargetID()) {
			creature->sendSystemMessage("To give consent, you must either specify the player name or target that player and use the command.");
			return GENERALERROR;
		} //TODO: How can we allow consent to be fired from toolbar with the command icon??

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
				}

				if (server->getZoneServer()->getPlayerManager()->existsName(name) && creature->getFirstName().toLowerCase() != name) {
					consent(creature, name);
				} else {
					creature->sendSystemMessage("You cannot give consent to yourself!");
					return INVALIDTARGET;
				}
			}
		} else {
			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
			CreatureObject* playerTarget = cast<CreatureObject*>( object.get());

			if (object == NULL || !object->isPlayerCreature() || object == creature) {
				//System::out << "invalid target" << endl;
				return INVALIDTARGET;
			}

			if (playerTarget != NULL)
				consent(creature, playerTarget->getFirstName().toLowerCase());

				StringIdChatParameter stringId2("base_player", "prose_got_consent"); // %TO consents you.
				stringId2.setTO(creature->getObjectID());
				if (playerTarget->isPlayerCreature()) {
					playerTarget->sendSystemMessage(stringId2);
				}
		}

		return SUCCESS;
	}

};

#endif //CONSENTCOMMAND_H_
