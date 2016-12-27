/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TELLPETCOMMAND_H_
#define TELLPETCOMMAND_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/creature/PetManager.h"

class TellpetCommand : public QueueCommand {
public:

	TellpetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> player = creature->getPlayerObject();
		if( player == NULL )
			return GENERALERROR;

		// Send message to all player's pets within range
		for (int i = 0; i < player->getActivePetsSize(); ++i) {

			ManagedReference<AiAgent*> pet = player->getActivePet(i);
			if (pet != NULL) {

				if( creature->isInRange( pet, 150.0 ) ){

					Locker clocker(pet, creature);
					server->getZoneServer()->getPetManager()->handleChat( creature, pet, arguments.toString() );
				}
			}
		}

		return SUCCESS;
	}

};

#endif //TELLPETCOMMAND_H_
