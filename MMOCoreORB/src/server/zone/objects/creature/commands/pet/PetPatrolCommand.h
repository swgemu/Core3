
#ifndef PETPATROLCOMMAND_H_
#define PETPATROLCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"

class PetPatrolCommand : public QueueCommand {
public:
	PetPatrolCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		// Check if droid has power
		if( controlDevice->getPetType() == PetManager::DROIDPET ) {
			ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(pet.get());
			if( droidPet == NULL )
				return GENERALERROR;

			if( !droidPet->hasPower() ){
				pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		// ignore if pet is in combat
		if (pet->isInCombat())
			return GENERALERROR;

		Locker clocker(controlDevice, creature);

		if (controlDevice->getPatrolPointSize() == 0)
			return GENERALERROR;

		pet->setFollowState(AiAgent::PATROLLING);
		pet->clearSavedPatrolPoints();
		pet->stopWaiting();
		pet->setWait(0);

		for (int i = 0; i < controlDevice->getPatrolPointSize(); i++) {
			PatrolPoint point = controlDevice->getPatrolPoint(i);
			pet->addPatrolPoint(point);
		}

		pet->activateMovementEvent();

		controlDevice->setLastCommand(PetManager::PATROL);

		return SUCCESS;
	}

};


#endif /* PETPATROLCOMMAND_H_ */
