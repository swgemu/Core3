/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CRIPPLINGSHOTCOMMAND_H_
#define CRIPPLINGSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class CripplingShotCommand : public CombatQueueCommand {
public:

	CripplingShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (creature == targetObject || targetObject == NULL)
			return INVALIDTARGET;

		CreatureObject* player = cast<CreatureObject*>( targetObject.get());

		Locker clocker(player, creature);

		PlayerManager* playerManager = server->getPlayerManager();

		if (!CollisionManager::checkLineOfSight(creature, player)) {
			creature->sendSystemMessage("@cbt_spam:los_recycle"); //You cannot see your target.
			return GENERALERROR;
		}

		WeaponObject* weapon = creature->getWeapon();

		int maxRange = weapon->getMaxRange();

		if(!checkDistance(creature, player, maxRange)) {
			creature->sendSystemMessage("@error_message:target_out_of_range");//Your target is out of range for this action.
			return TOOFAR;
		}

		return doCombatAction(creature, target);
	}

};

#endif //CRIPPLINGSHOTCOMMAND_H_
