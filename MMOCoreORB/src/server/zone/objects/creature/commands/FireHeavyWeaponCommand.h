/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREHEAVYWEAPONCOMMAND_H_
#define FIREHEAVYWEAPONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "engine/task/ScheduledTask.h"

class FireHeavyWeaponCommand : public CombatQueueCommand {
public:

	FireHeavyWeaponCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		try {

			uint64 weaponID = tokenizer.getLongToken();
			Reference<WeaponObject*> weapon = server->getZoneServer()->getObject(weaponID).castTo<WeaponObject*>();
			if (weapon == NULL || !weapon->isHeavyWeapon())
				return INVALIDPARAMETERS;

			if (!weapon->isASubChildOf(creature))
				return GENERALERROR;

			ManagedReference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target).castTo<TangibleObject*>();
			if (targetObject == NULL)
				return GENERALERROR;

			if (!(targetObject->isAttackableBy(creature)))
				return GENERALERROR;

			SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(weapon->getServerObjectCRC());

			if (templateData == NULL)
				return GENERALERROR;

			SharedWeaponObjectTemplate* weaponData = cast<SharedWeaponObjectTemplate*>(templateData);

			if (weaponData == NULL)
				return GENERALERROR;

			// TODO: This is probably actually determined by some combat result
			String animName = "fire_heavy_" + weaponData->getAnimationType() + (System::random(1) ? "_light" : "_medium");
			uint32 animCRC = animName.hashCode();

			UnicodeString args = "combatSpam=" + weaponData->getCombatSpam() + ";animationCRC=" + String::valueOf(animCRC) + ";";

			int result = doCombatAction(creature, target, args, weapon);

			if (result == SUCCESS) {
				// We need to give some time for the combat animation to start playing before destroying the tano
				SCHEDULE_TASK_1(weapon, 100, {

					Locker locker(weapon_p);
					weapon_p->decreaseUseCount();
				});
			}

			return result;

		} catch (Exception& e) {

		}

		return GENERALERROR;
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

#endif //FIREHEAVYWEAPONCOMMAND_H_
