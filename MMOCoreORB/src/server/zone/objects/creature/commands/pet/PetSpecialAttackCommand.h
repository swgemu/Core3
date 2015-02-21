
#ifndef PETSPECIALATTACKCOMMAND_H_
#define PETSPECIALATTACKCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetSpecialAttackCommand : public QueueCommand {
public:
	PetSpecialAttackCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().castTo<PetControlDevice*>();
		if (controlDevice == NULL)
			return GENERALERROR;

		int petType = controlDevice->getPetType();
		if( petType == PetManager::DROIDPET || petType == PetManager::FACTIONPET ) {
			return GENERALERROR;
		}

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);
		if( pet == NULL )
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target, true).castTo<TangibleObject*>();
		if (targetObject == NULL || !targetObject->isAttackableBy(pet) ) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return INVALIDTARGET;
		}

		ManagedReference<TangibleObject*> targetTano = targetObject.castTo<TangibleObject*>();

		int attackNumber = Integer::valueOf(arguments.toCharArray());

		if (attackNumber < 1 || attackNumber > 2)
			return INVALIDPARAMETERS;

		switch (attackNumber) {
		case 1:
			controlDevice->setLastCommand(PetManager::SPECIAL_ATTACK1);
			break;
		case 2:
			controlDevice->setLastCommand(PetManager::SPECIAL_ATTACK2);
			break;
		}

		controlDevice->setLastCommandTarget(targetTano);

		if (!pet->isInCombat()) {
			pet->activateInterrupt(pet->getLinkedCreature().get(), ObserverEventType::STARTCOMBAT);
		} else if (targetTano != pet->getFollowObject()) {
			pet->setDefender(targetTano);
		}

		pet->selectSpecialAttack(attackNumber - 1);
		pet->enqueueAttack(QueueCommand::FRONT);

		return SUCCESS;
	}

};


#endif /* PETSPECIALATTACKCOMMAND_H_ */
