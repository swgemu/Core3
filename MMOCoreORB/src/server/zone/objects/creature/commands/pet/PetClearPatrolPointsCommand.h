
#ifndef PETCLEARPATROLPOINTSCOMMAND_H_
#define PETCLEARPATROLPOINTSCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"

class PetClearPatrolPointsCommand : public QueueCommand {
public:
	PetClearPatrolPointsCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();
		if (controlDevice == nullptr)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if (pet == nullptr)
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		// Check if droid has power
		if (controlDevice->getPetType() == PetManager::DROIDPET) {
			ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(pet.get());
			if (droidPet == nullptr)
				return GENERALERROR;

			if (!droidPet->hasPower()) {
				pet->showFlyText("npc_reaction/flytext", "low_power", 204, 0, 0); // "*Low Power*"
				return GENERALERROR;
			}
		}

		// ignore if pet is in combat
		if (pet->isInCombat())
			return GENERALERROR;

		Locker clocker(controlDevice, creature);

		controlDevice->clearPatrolPoints();

		if (pet->getMovementState() == AiAgent::PATROLLING) {
			pet->setOblivious();
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target, true);
		if (targetObject != nullptr && targetObject->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>(targetObject.get());
			player->sendSystemMessage("@pet/pet_menu:patrol_removed"); // Patrol points forgotten
		}

		return SUCCESS;
	}
};

#endif /* PETCLEARPATROLPOINTSCOMMAND_H_ */
