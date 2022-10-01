
#ifndef PETTRANSFERCOMMAND_H_
#define PETTRANSFERCOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class PetTransferCommand : public QueueCommand {
public:
	PetTransferCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PetControlDevice*> controlDevice = creature->getControlDevice().get().castTo<PetControlDevice*>();

		if (controlDevice == nullptr)
			return GENERALERROR;

		// Creature specific command
		if (controlDevice->getPetType() != PetManager::CREATUREPET)
			return GENERALERROR;

		if (!creature->isAiAgent())
			return GENERALERROR;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(creature);

		if (pet == nullptr)
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = pet->getLinkedCreature().get();
		if (player == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> commandTarget = server->getZoneServer()->getObject(target);

		if (commandTarget == nullptr || !commandTarget->isPlayerCreature()) {
			player->sendSystemMessage("Your target must be a player to transfer a pet.");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> targetPlayer = cast<CreatureObject*>(commandTarget.get());

		Locker targetCrosslocker(targetPlayer, creature);

		if (!checkDistance(player, targetPlayer, 15)) {
			player->sendSystemMessage("@error_message:target_out_of_range"); // Your target is out of range for this action.
			return GENERALERROR;
		}

		if (!controlDevice->canBeTradedTo(player, targetPlayer, 0))
			return GENERALERROR;

		if (pet->isInCombat() || player->isInCombat() || targetPlayer->isInCombat())
			return GENERALERROR;

		if (pet->hasRidingCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> targetGhost = targetPlayer->getPlayerObject();
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (targetGhost == nullptr || ghost == nullptr)
			return GENERALERROR;

		int activePets = 0;
		int petLevel = 0;

		for (int i = 0; i < targetGhost->getActivePetsSize(); i++) {
			ManagedReference<AiAgent*> targetPet = targetGhost->getActivePet(i);

			ManagedReference<PetControlDevice*> device = targetPet->getControlDevice().get().castTo<PetControlDevice*>();

			if (device == nullptr)
				continue;

			if (device->getPetType() == PetManager::CREATUREPET) {
				activePets++;
				petLevel += targetPet->getLevel();
			}
		}

		// none ch doesn't seem to have keep_creature, effectively returns 0/
		if (activePets != 0 && activePets >= targetPlayer->getSkillMod("keep_creature")) {
			player->sendSystemMessage("@pet/pet_menu:targ_too_many");  // That person has too many pets. Transfer failed.
			targetPlayer->sendSystemMessage("@pet/pet_menu:too_many"); // You can't control any more pets. Store one first.
			return GENERALERROR;
		}

		// None CH can only have 1 active pet.
		if (targetPlayer->hasSkill("outdoors_creaturehandler_novice") && ((petLevel + pet->getLevel()) > targetPlayer->getSkillMod("tame_level"))) {
			player->sendSystemMessage("@pet/pet_menu:no_chance"); // That person has no chance of controlling this creature. Transfer failed.
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> targetDatapad = targetPlayer->getSlottedObject("datapad");

		if (targetDatapad == nullptr)
			return GENERALERROR;

		pet->setCreatureLink(targetPlayer);
		pet->setFaction(targetPlayer->getFaction());
		pet->setFollowObject(targetPlayer);
		pet->storeFollowObject();

		if (targetPlayer->getPvpStatusBitmask() & CreatureFlag::PLAYER)
			pet->setPvpStatusBitmask(targetPlayer->getPvpStatusBitmask() - CreatureFlag::PLAYER, true);
		else
			pet->setPvpStatusBitmask(targetPlayer->getPvpStatusBitmask(), true);

		targetDatapad->transferObject(controlDevice, -1);
		targetGhost->addToActivePets(pet);
		targetDatapad->broadcastObject(controlDevice, true);

		player->sendSystemMessage("@pet/pet_menu:pet_transfer_succeed"); // The pet has been successfully transferred

		targetCrosslocker.release();

		Locker plocker(player, pet);
		ghost->removeFromActivePets(pet);
		plocker.release();

		Locker deviceLocker(controlDevice);
		Locker targetLock(targetPlayer, controlDevice);

		controlDevice->setLastCommander(targetPlayer);
		controlDevice->setLastCommandTarget(nullptr);
		controlDevice->setLastCommand(PetManager::FOLLOW);

		return SUCCESS;
	}
};

#endif /* PETTRANSFERCOMMAND_H_ */
