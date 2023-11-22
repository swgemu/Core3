/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NPCCONVERSATIONSTARTCOMMAND_H_
#define NPCCONVERSATIONSTARTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

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

		if (object == nullptr || !object->isAiAgent())
			return INVALIDTARGET;

		AiAgent* agent = object->asAiAgent();

		if (agent == nullptr)
			return INVALIDTARGET;

		try {
			Locker clocker(agent, creature);

			ValidatedPosition* validPosition = ghost->getLastValidatedPosition();

			if (validPosition == nullptr)
				return GENERALERROR;

			Vector3 creaturePos = validPosition->getPosition();
			uint64 playerPaentID = validPosition->getParent();

			Vector3 agentPos = agent->getPosition();
			uint64 agentParentID = agent->getParentID();

			// No conversing from different cells
			if (playerPaentID != agentParentID) {
				return TOOFAR;
			}

			// If the conversing NPC is outdoors, we will acount for distance based on x, y only. LoS also checked below
			if (agentParentID == 0) {
				agentPos -= creaturePos;

				// Calculate the distance squared without use of the z coordinate. We also check LoS below
				float distanceSq = (agentPos.getX() * agentPos.getX() + agentPos.getY() * agentPos.getY());

				if (distanceSq > 25) {
					return TOOFAR;
				}
			} else if (creaturePos.squaredDistanceTo(agentPos) > 25) {
				return TOOFAR;
			}

			// No conversing without LoS
			if (!CollisionManager::checkLineOfSight(agent, creature)) {
				return GENERALERROR;
			}

			ghost->setConversatingCreature(agent);

			if (agent->sendConversationStartTo(creature)) {
				agent->notifyObservers(ObserverEventType::STARTCONVERSATION, creature);
			}
		} catch (Exception& e) {
			e.printStackTrace();
			creature->error("unreported ObjectControllerMessage::parseNpcStartConversation(creature* creature, Message* pack) exception");
		}

		return SUCCESS;
	}
};

#endif //NPCCONVERSATIONSTARTCOMMAND_H_
