
#ifndef PETATTACKCOMMAND_H_
#define PETATTACKCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/combat/CombatManager.h"

class PetAttackCommand : public QueueCommand {
public:
	PetAttackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

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
				creature->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		// TODO: allow non-player targets when Ai vs Ai combat is enabled
		Reference<SceneObject*> targetObject = server->getZoneServer()->getObject(target, true).castTo<SceneObject*>();
		if (targetObject == NULL || !targetObject->isPlayerCreature() ) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			ManagedReference<CreatureObject*> player = pet->getLinkedCreature().get();
			if (player != NULL)
				player->sendSystemMessage("Pets may only attack players right now.");
			return GENERALERROR;
		}

		ManagedReference<TangibleObject*> targetTano = targetObject.castTo<TangibleObject*>();

		CombatManager* combatManager = CombatManager::instance();

		combatManager->startCombat(pet, targetTano);

		return SUCCESS;
	}

};


#endif /* PETATTACKCOMMAND_H_ */
