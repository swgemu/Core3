
#ifndef PETCLEARPATROLPOINTSCOMMAND_H_
#define PETCLEARPATROLPOINTSCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"

class PetClearPatrolPointsCommand : public QueueCommand {
public:
	PetClearPatrolPointsCommand(const String& name, ZoneProcessServer* server)
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

		controlDevice->clearPatrolPoints();

		if (pet->getFollowState() == AiAgent::PATROLLING) {
			pet->setOblivious();
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target, true);
		if (targetObject != NULL || targetObject->isPlayerCreature() ) {
			CreatureObject* player = cast<CreatureObject*>(targetObject.get());
			player->sendSystemMessage("@pet/pet_menu:patrol_removed"); // Patrol points forgotten
		}

		return SUCCESS;
	}

};


#endif /* PETCLEARPATROLPOINTSCOMMAND_H_ */
