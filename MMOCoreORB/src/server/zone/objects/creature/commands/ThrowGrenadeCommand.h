/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef THROWGRENADECOMMAND_H_
#define THROWGRENADECOMMAND_H_

#include "engine/core/TaskManager.h"

class ThrowGrenadeCommand : public CombatQueueCommand {
public:

	ThrowGrenadeCommand(const String& name, ZoneProcessServer* server)
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
			Reference<WeaponObject*> grenade = server->getZoneServer()->getObject(weaponID).castTo<WeaponObject*>();
			if (grenade == NULL)
				return INVALIDPARAMETERS;

			if (!grenade->isThrownWeapon())
				return INVALIDPARAMETERS;

			if (!grenade->isASubChildOf(creature))
				return GENERALERROR;

			ManagedReference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target).castTo<TangibleObject*>();
			if (targetObject == NULL)
				return GENERALERROR;

			if (!(targetObject->isAttackableBy(creature)))
				return GENERALERROR;

			SharedObjectTemplate* templateData = TemplateManager::instance()->getTemplate(grenade->getServerObjectCRC());

			if (templateData == NULL)
				return GENERALERROR;

			SharedWeaponObjectTemplate* grenadeData = cast<SharedWeaponObjectTemplate*>(templateData);

			if (grenadeData == NULL)
				return GENERALERROR;

			UnicodeString args = "combatSpam=" + grenadeData->getCombatSpam() + ";";

			int result = doCombatAction(creature, target, args, grenade);

			if (result == SUCCESS) {
				// We need to give some time for the combat animation to start playing before destroying the tano
				// otherwise our character will play the wrong animations

				Core::getTaskManager()->scheduleTask([grenade] {
					Locker lock(grenade);
					grenade->decreaseUseCount();
				}, "ThrowGrenadeTanoDecrementTask", 100);
			}

			return result;

		} catch (Exception& e) {

		}

		return GENERALERROR;
	}

	String getAnimation(TangibleObject* attacker, TangibleObject* defender, WeaponObject* weapon, uint8 hitLocation, int damage) const {
		SharedWeaponObjectTemplate* weaponData = cast<SharedWeaponObjectTemplate*>(weapon->getObjectTemplate());

		if (weaponData == NULL) {
			warning("Null weaponData in ThrowGrenadeCommand::getAnimation");
			return "";
		}

		String type = weaponData->getAnimationType();
		if (type.isEmpty())
			return "throw_grenade";

		int range = attacker->getWorldPosition().distanceTo(defender->getWorldPosition());

		String distance = "";
		if (range < 10) {
			distance = "_near_";
		} else if (range < 20) {
			distance = "_medium_";
		} else {
			distance = "_far_";
		}

		return "throw_grenade" + distance + type;
	}

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) const {
		StringTokenizer tokenizer(arguments.toString());
		uint64 weaponID = tokenizer.getLongToken();

		Reference<WeaponObject*> grenade = server->getZoneServer()->getObject(weaponID).castTo<WeaponObject*>();

		if (grenade != NULL)
			return CombatManager::instance()->calculateWeaponAttackSpeed(object, grenade, speedMultiplier);
		else
			return defaultTime * speedMultiplier;
	}

};

#endif //THROWGRENADECOMMAND_H_
