/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONCEALSHOTCOMMAND_H_
#define CONCEALSHOTCOMMAND_H_

#include "CombatQueueCommand.h"

class ConcealShotCommand : public CombatQueueCommand {
public:

	ConcealShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target);

		if (targetObject == nullptr)
			return GENERALERROR;

		int result = doCombatAction(creature, target);

		if (result == SUCCESS && creature->isPlayerCreature() && targetObject->isCreatureObject()) {
			CreatureObject* tarCreo = targetObject->asCreatureObject();

			if (tarCreo == nullptr || tarCreo->isDead() || !tarCreo->isAiAgent()) {
				return result;
			}

			AiAgent* agent = tarCreo->asAiAgent();

			if (agent != nullptr) {
				int missCount = 0;
				VectorMap<uint64, int>* targetMissCount = agent->getTargetMissCount();

				Locker creoLock(agent);

				if (targetMissCount != nullptr) {
					for (int i = 0; i < targetMissCount->size(); ++i){
						uint64 listTarget = targetMissCount->elementAt(i).getKey();

						if (listTarget == creature->getObjectID()) {
							missCount = targetMissCount->elementAt(i).getValue();

							break;
						}
					}
				}

				float distSq = 40.f * 40.f;

				if (creature->getWorldPosition().squaredDistanceTo(agent->getWorldPosition()) >= distSq) {
					int posture = creature->getPosture();

					if ((posture == CreaturePosture::PRONE && missCount <= 3) || (posture == CreaturePosture::CROUCHED && missCount <= 2) || (posture == CreaturePosture::UPRIGHT && missCount <= 1)) {
						ThreatMap* threatMap = agent->getThreatMap();

						if (threatMap != nullptr && threatMap->size() > 0) {
							for (int i = 0; i < threatMap->size(); ++i) {
								TangibleObject* threatTano = threatMap->elementAt(i).getKey();

								if (threatTano == nullptr) {
									continue;
								}

								if (threatTano == creature) {
									threatMap->remove(i);
									break;
								}
							}
						}
					}
				}
			}
		}

		return result;
	}

};

#endif //CONCEALSHOTCOMMAND_H_
