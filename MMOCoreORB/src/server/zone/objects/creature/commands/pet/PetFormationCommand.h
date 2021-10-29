#ifndef PETFORMATIONCOMMAND_H_
#define PETFORMATIONCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetFormationCommand : public QueueCommand {
public:
	PetFormationCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		if (pet->getPosture() != CreaturePosture::UPRIGHT && pet->getPosture() != CreaturePosture::KNOCKEDDOWN)
			pet->setPosture(CreaturePosture::UPRIGHT);

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens()) {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return GENERALERROR;
		}

		String formationType = tokenizer.getStringToken();

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

		// attempt peace if the pet is in combat
		if (pet->isInCombat())
			CombatManager::instance()->attemptPeace(pet);

		ManagedReference<CreatureObject*> owner = pet->getLinkedCreature().get();

		if (owner == nullptr)
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = owner->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		int petNumber = 0;
		int activePetsSize = ghost->getActivePetsSize();

		for (int i = 0; i < activePetsSize; ++i) {
			ManagedReference<AiAgent*> listPet = ghost->getActivePet(i);

			if (listPet == nullptr)
				continue;

			if (listPet == pet) {
				petNumber = i + 1;
				break;
			}
		}

		if (petNumber % 2 == 0) {
			petNumber *= -1;
		} else {
			petNumber += 1;
		}

		Vector3 formationOffset;

		if (formationType == "column") {
			formationOffset.setX(petNumber);
		} else if (formationType == "wedge") {
			formationOffset.setX(petNumber);
			formationOffset.setY(fabs(petNumber) * -1);
		}

		pet->writeBlackboard("formationOffset", formationOffset);

		return SUCCESS;
	}
};

#endif /* PETFORMATIONCOMMAND_H_ */