/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESCUECOMMAND_H_
#define RESCUECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

class RescueCommand : public QueueCommand {
public:

	RescueCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if(!creature->isPlayerCreature() || !creature->isGrouped())
			return INVALIDTARGET;

		ManagedReference<CreatureObject* > targetCreature =
				server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

		if(targetCreature == NULL)
			return INVALIDTARGET;

		Locker crossLocker(targetCreature, creature);

		if(!targetCreature->isInCombat())
			return INVALIDTARGET;

		Locker clocker(targetCreature, creature);

		ManagedReference<SceneObject*> mainDefender = targetCreature->getMainDefender();

		if(mainDefender == NULL || !mainDefender->isCreatureObject())
			return INVALIDTARGET;

		ManagedReference<CreatureObject*> rescuedPlayer = mainDefender->asCreatureObject();

		if(rescuedPlayer == NULL)
			return INVALIDTARGET;

		if(rescuedPlayer->getGroup() != creature->getGroup())
			return INVALIDTARGET;

		/// Attempt Rescue, Skill range = 10-50
		float rescueMod = (float) creature->getSkillMod("rescue");

		if (rescueMod > 100.0f) {
			rescueMod = 100.0f;
		}

		int chanceRoll = System::random(50) + rescueMod;
		if(chanceRoll > 30) {
			ThreatMap* threatMap = targetCreature->getThreatMap();
			if(threatMap->setThreatState(creature, ThreatStates::TAUNTED, 5000, 5000)) {
				CombatManager::instance()->broadcastCombatSpam(creature, rescuedPlayer, NULL, 0, "cbt_spam", "rescue_success", 0);
				return SUCCESS;
			}
		}

		CombatManager::instance()->broadcastCombatSpam(creature, rescuedPlayer, NULL, 0, "cbt_spam", "rescue_fail", 0);

		return SUCCESS;
	}

};

#endif //RESCUECOMMAND_H_
