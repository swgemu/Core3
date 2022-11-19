
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
	PetFollowCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target, true);

		if (targetObject == nullptr || !targetObject->isCreatureObject()) {  // pets should be able to follow other mobiles as a command. i found multiple references to this. -- washu
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 playerID = tokenizer.getLongToken();

		ManagedReference<CreatureObject*> player = zoneServer->getObject(playerID, true).castTo<CreatureObject*>();

		if (player == nullptr)
			return GENERALERROR;

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		if (targetCreature == nullptr)
			return GENERALERROR;

		if (targetCreature != player && (targetCreature->isAttackableBy(creature) || !CollisionManager::checkLineOfSight(player, targetObject))) {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return INVALIDTARGET;
		}

		Reference<CellObject*> targetCell = targetObject->getParent().get().castTo<CellObject*>();

		if (targetCell != nullptr) {
			auto perms = targetCell->getContainerPermissions();

			if (!perms->hasInheritPermissionsFromParent()) {
				if (!targetCell->checkContainerPermission(player, ContainerPermissions::WALKIN)) {
					pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
					return INVALIDTARGET;
				}
			}
		}

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

		Locker clocker(controlDevice, creature);
		controlDevice->setLastCommandTarget(targetObject);
		clocker.release();

		pet->setFollowObject(targetObject);
		pet->storeFollowObject();

		if (pet->isResting()) {
			pet->setMovementState(AiAgent::FOLLOWING);
		}

		pet->notifyObservers(ObserverEventType::STARTCOMBAT, pet->getLinkedCreature().get());

		return SUCCESS;
	}
};

#endif /* PETFOLLOWCOMMAND_H_ */
