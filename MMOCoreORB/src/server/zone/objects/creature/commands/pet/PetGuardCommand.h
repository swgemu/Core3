
#ifndef PETGUARDCOMMAND_H_
#define PETGUARDCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetGuardCommand : public QueueCommand {
public:
	PetGuardCommand(const String& name, ZoneProcessServer* server)
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
		if (player == NULL || player->isAttackableBy(pet)) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		// Guard the player's target if valid, otherwise guard the player
		uint64 playersTargetID = player->getTargetID();

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(playersTargetID, true).castTo<TangibleObject*>();
		if (targetObject == NULL || !targetObject->isCreatureObject() || targetObject->isAttackableBy(pet)) {
			targetObject = player->asTangibleObject();
		}

		pet->setFollowObject(targetObject);
		pet->storeFollowObject();

		Locker clocker(controlDevice, creature);
		controlDevice->setLastCommand(PetManager::GUARD);
		controlDevice->setLastCommandTarget(targetObject);

		pet->activateInterrupt(pet->getLinkedCreature().get(), ObserverEventType::STARTCOMBAT);

		return SUCCESS;
	}

};


#endif /* PETGUARDCOMMAND_H_ */
