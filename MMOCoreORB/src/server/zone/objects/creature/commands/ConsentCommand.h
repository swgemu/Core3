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

		StringIdChatParameter stringId("base_player", "prose_consent");
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

		//System::out << "past initiali checks ConsentCommand" << endl;

		CreatureObject* player = cast<CreatureObject*>(creature);

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost->getConsentListSize() >= 20) {
			player->sendSystemMessage("You are consenting too many people");
			return GENERALERROR;
		}

		if (!arguments.isEmpty()) {
			StringTokenizer tokenizer(arguments.toString());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String name = "";
				tokenizer.getStringToken(name);
				name = name.toLowerCase();

				if (server->getZoneServer()->getPlayerManager()->existsName(name))
					consent(player, name);
			}
		} else {
			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

			if (object == NULL || !object->isPlayerCreature() || object == creature) {
				//System::out << "invalid target" << endl;
				return INVALIDTARGET;
			}

			CreatureObject* playerTarget = cast<CreatureObject*>( object.get());

			consent(player, playerTarget->getFirstName().toLowerCase());

			StringIdChatParameter stringId2("base_player", "prose_got_consent");
			stringId2.setTO(player->getObjectID());
			playerTarget->sendSystemMessage(stringId2);
		}

		return SUCCESS;
	}

};

#endif //CONSENTCOMMAND_H_
