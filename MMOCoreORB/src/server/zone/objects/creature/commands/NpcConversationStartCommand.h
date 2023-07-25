/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTARTCOMMAND_H_
#define NPCCONVERSATIONSTARTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ai/SpaceStationObject.h"

class NpcConversationStartCommand : public QueueCommand {
public:

	NpcConversationStartCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == nullptr)
			return GENERALERROR;

		if (object->isCreatureObject()) {
			CreatureObject* agentCreo = cast<CreatureObject*>(object.get());

			if (agentCreo == nullptr)
				return GENERALERROR;

			try {
				Locker clocker(agentCreo, creature);

				ValidatedPosition* validPosition = ghost->getLastValidatedPosition();
				uint64 parentid = validPosition->getParent();

				if (parentid != agentCreo->getParentID()) {
					return TOOFAR;
				}

				if (checkDistance(creature, agentCreo, 5)) {
					ghost->setConversatingObject(agentCreo);

					if (agentCreo->sendConversationStartTo(creature)) {
						agentCreo->notifyObservers(ObserverEventType::STARTCONVERSATION, creature);
					}
				} else {
					return TOOFAR;
				}

			} catch (Exception& e) {
				e.printStackTrace();
				creature->error("unreported ObjectControllerMessage::parseNpcStartConversation(creature* creature, Message* pack) exception");
			}
		} else if (object->isSpaceStationObject()) {
			try {
				SpaceStationObject* spaceStationObj = cast<SpaceStationObject*>(object.get());

				if (spaceStationObj == nullptr)
					return INVALIDTARGET;

				Locker lock(spaceStationObj, creature);

				ghost->setConversatingObject(spaceStationObj);

				if (spaceStationObj->sendConversationStartTo(creature))
					spaceStationObj->notifyObservers(ObserverEventType::STARTCONVERSATION, creature);
			} catch (Exception& e) {
				e.printStackTrace();
			}
		}

		return SUCCESS;
	}
};

#endif //NPCCONVERSATIONSTARTCOMMAND_H_
