/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CONCEALSHOTCOMMAND_H_
#define CONCEALSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
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

		int size = creature->getAttackHistorySize();
		info("attack history size: " + String::valueOf(size), true);

		int res =  doCombatAction(creature, target);

		if(res == SUCCESS) {
			ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
			if(targetObject != NULL) {
				AiAgent *ai = targetObject->asAiAgent();
				if(ai != NULL) {
					Locker locker(ai, creature);
					ai->getDefenderList()->removeAll(NULL);
					CombatManager::instance()->forcePeace(ai);
				}
			}
		}

		return res;
	}

};

#endif //CONCEALSHOTCOMMAND_H_
