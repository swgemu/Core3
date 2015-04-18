/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEWEAKEN2COMMAND_H_
#define FORCEWEAKEN2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class ForceWeaken2Command : public ForcePowersQueueCommand {
public:

	ForceWeaken2Command(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Setup debuff.

			Reference<SceneObject*> object = server->getZoneServer()->getObject(target);
			ManagedReference<CreatureObject*> creatureTarget = cast<CreatureObject*>( object.get());

			if (creatureTarget != NULL) {
				ManagedReference<Buff*> buff = new Buff(creatureTarget, getNameCRC(), 120, BuffType::JEDI);
				buff->setAttributeModifier(CreatureAttribute::HEALTH, -600);
				buff->setAttributeModifier(CreatureAttribute::ACTION, -600);
				buff->setAttributeModifier(CreatureAttribute::MIND, -600);

				creatureTarget->addBuff(buff);
			}

		}

		return SUCCESS;
	}

};

#endif //FORCEWEAKEN2COMMAND_H_
