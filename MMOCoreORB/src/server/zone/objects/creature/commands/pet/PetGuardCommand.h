
#ifndef PETGUARDCOMMAND_H_
#define PETGUARDCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/managers/creature/PetManager.h"

class PetGuardCommand : public QueueCommand {
public:
	PetGuardCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		// target is passed from PetManagerImplementation as the player giving the pet the command
		Reference<CreatureObject*> commander = server->getZoneServer()->getObject(target, true).castTo<CreatureObject*>();

		if (commander == nullptr) {
			return GENERALERROR;
		}

		if (commander->isSwimming() || pet->isSwimming()) {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return GENERALERROR;
		}

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		// Guard the commanding player's target if valid, otherwise guard the player
		uint64 playersTargetID = commander->getTargetID();

		Reference<TangibleObject*> targetObject = zoneServer->getObject(playersTargetID, true).castTo<TangibleObject*>();

		if (targetObject == nullptr || targetObject->isAttackableBy(commander)) {
			targetObject = commander;
		}

		 if (targetObject != commander && (!CollisionManager::checkLineOfSight(commander, targetObject) || !playerEntryCheck(commander, targetObject))) {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?!!?!?!"
			return GENERALERROR;
		}

		pet->setFollowObject(targetObject);
		pet->storeFollowObject();

		Locker clocker(controlDevice, creature);
		controlDevice->setLastCommandTarget(targetObject);

		pet->notifyObservers(ObserverEventType::STARTCOMBAT, targetObject);

		return SUCCESS;
	}
};

#endif /* PETGUARDCOMMAND_H_ */
