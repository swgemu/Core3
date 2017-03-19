
#ifndef PETRANGEDATTACKCOMMAND_H_
#define PETRANGEDATTACKCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/managers/creature/PetManager.h"

class PetRangedAttackCommand : public QueueCommand {
public:
	PetRangedAttackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		if (pet->getPosture() != CreaturePosture::UPRIGHT && pet->getPosture() != CreaturePosture::KNOCKEDDOWN)
			pet->setPosture(CreaturePosture::UPRIGHT);

		// Check if droid has power
		if( controlDevice->getPetType() == PetManager::DROIDPET ){
			ManagedReference<DroidObject*> droidPet = cast<DroidObject*>(pet.get());
			if( droidPet == NULL )
				return GENERALERROR;

			if( !droidPet->hasPower() ){
				pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		Reference<CreatureObject*> player = server->getZoneServer()->getObject(target, true).castTo<CreatureObject*>();
		if (player == NULL || !player->isPlayerCreature()) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		Locker clocker(controlDevice, creature);

		if (controlDevice->getUseRanged()) {
			player->sendSystemMessage("@pet/pet_menu:ranged_attack_toggled_off"); // Pet ranged attack mode toggled OFF
		} else {
			player->sendSystemMessage("@pet/pet_menu:ranged_attack_toggled"); // Pet ranged attack mode toggled ON
		}

		controlDevice->toggleUseRanged();

		pet->selectWeapon();

		return SUCCESS;
	}

};


#endif /* PETRANGEDATTACKCOMMAND_H_ */
