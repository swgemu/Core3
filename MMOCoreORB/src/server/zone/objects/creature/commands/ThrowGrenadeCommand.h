/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef THROWGRENADECOMMAND_H_
#define THROWGRENADECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

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
				Locker locker(grenade);

				grenade->decreaseUseCount();
			}

			return result;

		} catch (Exception& e) {

		}

		return GENERALERROR;
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
