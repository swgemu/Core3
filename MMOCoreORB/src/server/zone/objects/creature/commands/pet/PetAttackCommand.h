
#ifndef PETATTACKCOMMAND_H_
#define PETATTACKCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetAttackCommand : public QueueCommand {
public:
	PetAttackCommand(const String& name, ZoneProcessServer* server)
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
				creature->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return GENERALERROR;
			}
		}

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target, true).castTo<TangibleObject*>();
		if (targetObject == NULL || !targetObject->isAttackableBy(pet) ) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return INVALIDTARGET;
		}

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 playerID = tokenizer.getLongToken();

		Reference<CreatureObject*> player = server->getZoneServer()->getObject(playerID, true).castTo<CreatureObject*>();

		if (player == NULL)
			return GENERALERROR;

		if (player->isSwimming()) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		if (!CollisionManager::checkLineOfSight(player, targetObject)) {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return INVALIDTARGET;
		}

		Reference<CellObject*> targetCell = targetObject->getParent().get().castTo<CellObject*>();

		if (targetCell != NULL) {
			ContainerPermissions* perms = targetCell->getContainerPermissions();

			if (!perms->hasInheritPermissionsFromParent()) {
				if (!targetCell->checkContainerPermission(player, ContainerPermissions::WALKIN)) {
					pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
					return INVALIDTARGET;
				}
			}
		}

		ManagedReference<TangibleObject*> targetTano = targetObject.castTo<TangibleObject*>();

		Locker clocker(controlDevice, creature);
		controlDevice->setLastCommand(PetManager::ATTACK);
		controlDevice->setLastCommandTarget(targetTano);

		pet->activateInterrupt(pet->getLinkedCreature().get(), ObserverEventType::STARTCOMBAT);

		pet->selectDefaultAttack();
		pet->enqueueAttack(QueueCommand::FRONT);

		return SUCCESS;
	}

};


#endif /* PETATTACKCOMMAND_H_ */
