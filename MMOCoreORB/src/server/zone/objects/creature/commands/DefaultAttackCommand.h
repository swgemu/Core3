/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEFAULTATTACKCOMMAND_H_
#define DEFAULTATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class DefaultAttackCommand : public CombatQueueCommand {
public:

	DefaultAttackCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isAiAgent())
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		CreatureObject *targetCreo = targetObject->asCreatureObject();
		unsigned long targetID = targetCreo->getTargetID();

		if(targetID == 0)
			return INVALIDTARGET;

		WeaponObject* weapon = creature->getWeapon();
		int maxRange = weapon->getMaxRange();

		if (!targetObject->isInRange(creature, maxRange + targetObject->getTemplateRadius() + creature->getTemplateRadius()))
			creature->sendSystemMessage("@combat_spam:out_of_range_single"); // That target is out of range.
			return TOOFAR;

		return doCombatAction(creature, target, arguments);
	}

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) const {
		StringTokenizer tokenizer(arguments.toString());
		uint64 weaponID = tokenizer.getLongToken();
		ManagedReference<WeaponObject*> weapon = server->getZoneServer()->getObject(weaponID).castTo<WeaponObject*>();

		if (weapon != NULL)
			return CombatManager::instance()->calculateWeaponAttackSpeed(object, weapon, speedMultiplier);
		else
			return defaultTime * speedMultiplier;
	}

};

#endif //DEFAULTATTACKCOMMAND_H_
