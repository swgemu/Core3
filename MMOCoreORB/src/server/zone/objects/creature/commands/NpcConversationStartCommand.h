/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTARTCOMMAND_H_
#define NPCCONVERSATIONSTARTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class NpcConversationStartCommand : public QueueCommand {
public:

	NpcConversationStartCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		if (!creature->isPlayerCreature()) {
			return GENERALERROR;
		}

		CreatureObject* player = cast<CreatureObject*>(creature);
		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && object->isCreatureObject()) {
			CreatureObject* creatureObject = cast<CreatureObject*>(object.get());

			try {
				Locker clocker(creatureObject, creature);
				ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
				uint64 parentid = validPosition->getParent();
				if (parentid != creatureObject->getParentID()) {
					return TOOFAR;
				}

				if (player->getDistanceTo(creatureObject) <= 5.f) {
					ghost->setConversatingCreature(creatureObject);
					if (creatureObject->sendConversationStartTo(creature)) {
						creatureObject->notifyObservers(ObserverEventType::STARTCONVERSATION, player);
					}
				} else {
					return TOOFAR;
				}

			} catch (Exception& e) {
				e.printStackTrace();
				creature->error("unreported ObjectControllerMessage::parseNpcStartConversation(creature* creature, Message* pack) exception");
			}
		} else {
			return INVALIDTARGET;
		}
		return SUCCESS;
	}

};

#endif //NPCCONVERSATIONSTARTCOMMAND_H_
