
#ifndef PETFOLLOWCOMMAND_H_
#define PETFOLLOWCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetFollowCommand : public QueueCommand {
public:
	PetFollowCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();

		if (controlDevice == NULL)
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);

		if (pet == NULL)
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		if (pet->getPosture() != CreaturePosture::UPRIGHT && pet->getPosture() != CreaturePosture::KNOCKEDDOWN)
			pet->setPosture(CreaturePosture::UPRIGHT);

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target, true);
		if (targetObject == NULL || !targetObject->isCreatureObject() ) { // pets should be able to follow other mobiles as a command. i found multiple references to this. -- washu
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 playerID = tokenizer.getLongToken();

		ManagedReference<CreatureObject*> player = server->getZoneServer()->getObject(playerID, true).castTo<CreatureObject*>();

		if (player == NULL)
			return GENERALERROR;

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		if (targetCreature == NULL)
			return GENERALERROR;

		if (targetCreature != player && targetCreature->isAttackableBy(creature) && !CollisionManager::checkLineOfSight(player, targetObject)) {
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
		// attempt peace if the pet is in combat
		if (pet->isInCombat())
			CombatManager::instance()->attemptPeace(pet);

		pet->setFollowObject(targetObject);
		pet->storeFollowObject();

		Locker clocker(controlDevice, creature);
		controlDevice->setLastCommand(PetManager::FOLLOW);

		pet->activateInterrupt(pet->getLinkedCreature().get(), ObserverEventType::STARTCOMBAT);

		return SUCCESS;
	}

};


#endif /* PETFOLLOWCOMMAND_H_ */
