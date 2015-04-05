/*
 * PetRecoverCommand.h
 *
 *  Created on: Feb 23, 2014
 *      Author: Klivian
 */

#ifndef PETRECOVERCOMMAND_H_
#define PETRECOVERCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/AiAgent.h"

class PetRecoverCommand : public QueueCommand {
public:
	PetRecoverCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		if (!creature->isAiAgent())
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		ManagedReference< CreatureObject*> player = pet->getLinkedCreature().get();
		if( player == NULL )
			return GENERALERROR;

		Locker crossLocker(player, pet);

		// Check pet states
		if( !pet->isIncapacitated() )
			return GENERALERROR;

		if( pet->getHAM( CreatureAttribute::HEALTH ) <= 0 )
			pet->healDamage( player, CreatureAttribute::HEALTH, 1 - pet->getHAM( CreatureAttribute::HEALTH ) );

		if( pet->getHAM( CreatureAttribute::ACTION ) <= 0 )
			pet->healDamage( player, CreatureAttribute::ACTION, 1 - pet->getHAM( CreatureAttribute::ACTION ) );

		if( pet->getHAM( CreatureAttribute::MIND ) <= 0 )
			pet->healDamage( player, CreatureAttribute::MIND, 1 - pet->getHAM( CreatureAttribute::MIND ) );

		// Player animation
		player->doAnimation("heal_other");

		return SUCCESS;
	}

};


#endif /* PETRECOVERCOMMAND_H_ */
