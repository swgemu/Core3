
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/ValidMountScaleRange.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/creature/events/PetIncapacitationRecoverTask.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreObjectTask.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/EnqueuePetCommand.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"

void PetManagerImplementation::loadLuaConfig() {
	info("Loading configuration file.", true);

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/pet_manager.lua");

	LuaObject luaObject = lua->getGlobalObject("mountSpeedData");

	if (luaObject.isValidTable()) {
		for (int i = 1; i <= luaObject.getTableSize(); ++i) {
			LuaObject speedData = luaObject.getObjectAt(i);

			if (speedData.isValidTable()) {
				String filename = speedData.getStringAt(1);
				float runSpeed = speedData.getFloatAt(2);
				float gallopSpeedMultiplier = speedData.getFloatAt(3);
				int gallopDuration = speedData.getIntAt(4);
				int gallopCooldown = speedData.getIntAt(5);

				Reference<MountSpeedData*> data = new MountSpeedData(filename, runSpeed, gallopSpeedMultiplier, gallopDuration, gallopCooldown);

				mountSpeedData.add(data);
			}

			speedData.pop();
		}
	}

	luaObject.pop();

	info("Loaded " + String::valueOf(mountSpeedData.size()) + " mount speeds.", true);

	delete lua;
	lua = nullptr;
}

void PetManagerImplementation::loadValidMountScaleRanges() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/mount/valid_scale_range.iff");

	if (iffStream == nullptr) {
		error("Could not load valid mount scales.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ValidMountScaleRange*> validMountScale = new ValidMountScaleRange();
		validMountScale->parseDataTableRow(row);

		validMountScaleRanges.add(validMountScale);
	}

	info("Loaded " + String::valueOf(validMountScaleRanges.size()) + " mount scale ranges.", true);
}

short PetManagerImplementation::isValidMountScale(const String& appearanceFilename, int saddleCapacity, float scale) {
	for (int i = 0; i < validMountScaleRanges.size(); i++) {
		ValidMountScaleRange* range = validMountScaleRanges.get(i);

		if (range == nullptr)
			continue;

		if (appearanceFilename == range->getAppearanceFilename() && saddleCapacity == range->getSaddleCapacity()) {
			if (scale < range->getValidScaleMin())
				return TOOSMALL;
			else if (scale > range->getValidScaleMax())
				return TOOLARGE;
			else
				return CANBEMOUNTTRAINED;
		}
	}

	return INVALIDCREATURE;
}

short PetManagerImplementation::checkMountEligibility(PetControlDevice* petControlDevice, float height) {
	ManagedReference<TangibleObject*> controlledObject = petControlDevice->getControlledObject();
	if (controlledObject == nullptr || !controlledObject->isAiAgent())
		return PetManager::INVALIDCREATURE;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if (pet == nullptr)
		return PetManager::INVALIDCREATURE;

	// Check if the pet's species is able to be trained as a mount
	if (!pet->hasSlotDescriptor("rider"))
		return PetManager::INVALIDCREATURE;

	SharedObjectTemplate* objectTemplate = petControlDevice->getObjectTemplate();
	if (objectTemplate == nullptr)
		return PetManager::INVALIDCREATURE;

	short result;

	if (height == -1)
		result = isValidMountScale(objectTemplate->getAppearanceFilename(), 1, pet->getHeight());
	else
		result = isValidMountScale(objectTemplate->getAppearanceFilename(), 1, height);

	return result;
}

MountSpeedData* PetManagerImplementation::getMountSpeedData(const String& appearanceFilename) {
	for (int i = 0; i < mountSpeedData.size(); i++) {
		Reference<MountSpeedData*> data = mountSpeedData.get(i);

		if (appearanceFilename == data->getAppearanceFilename())
			return data;
	}

	return nullptr;
}

float PetManagerImplementation::getMountedRunSpeed(CreatureObject* mount) {
	if (!mount->isMount())
		return mount->getRunSpeed();

	ManagedReference<PetControlDevice*> pcd = mount->getControlDevice().get().castTo<PetControlDevice*>();

	if (pcd != nullptr) {
		SharedObjectTemplate* objectTemplate = pcd->getObjectTemplate();

		if (objectTemplate != nullptr) {
			MountSpeedData* mountSpeedData = getMountSpeedData(objectTemplate->getAppearanceFilename());

			if (mountSpeedData != nullptr)
				return mountSpeedData->getRunSpeed();
		}
	}

	return mount->getRunSpeed();
}

void PetManagerImplementation::handleChat(CreatureObject* speaker, AiAgent* pet, const String& message) {
	if (speaker == nullptr || pet == nullptr)
		return;

	if (message.isEmpty())
		return;

	if (pet->isDead() || pet->isIncapacitated())
		return;

	ManagedReference<PetControlDevice*> pcd = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (pcd == nullptr)
		return;

	// Handle command training
	if (pcd->getTrainingCommand() > 0) {
		bool ownerChat = handleCommandTraining(speaker, pet, message);
		if (ownerChat) {
			Locker locker(pcd);
			pcd->setTrainingCommand(0); // no longer training
		}

		return;
	}

	ManagedReference<CreatureObject*> linkedCreature = pet->getLinkedCreature().get();
	if (linkedCreature == nullptr)
		return;

	// Check if speaker has permission to command pet
	if (linkedCreature != speaker && !pcd->isFriend(speaker->getObjectID()))
		return;

	if (linkedCreature != speaker && pcd->getPetType() == PetManager::FACTIONPET && (speaker->getFaction() != pet->getFaction() || speaker->getFactionStatus() < FactionStatus::COVERT))
		return;

	ManagedReference<SceneObject*> speakerParent = speaker->getRootParent();
	ManagedReference<SceneObject*> petParent = pet->getRootParent();

	// If speaker is mounted, pet must be outdoors
	if (speaker->isRidingMount() && petParent != nullptr)
		return;

	// If speaker is unmounted, pet and speaker must both be outdoors or inside same building
	if (!speaker->isRidingMount() && speakerParent != petParent)
		return;

	// Handle trained command
	int command = getTrainedCommandNum(pcd, message);

#ifdef PET_DEBUG
	StringBuffer debugMsg;
	debugMsg << " command given " << message << " command number = " << command;
	speaker->sendSystemMessage(debugMsg.toString());
#endif

	if (command == STAY) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petstay"), "");
	} else if (command == FOLLOW) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petfollow"), String::valueOf(speaker->getObjectID()), true);
	} else if (command == STORE) {
		enqueueOwnerOnlyPetCommand(speaker, pet, STRING_HASHCODE("petstore"), "");
	} else if (command == ATTACK) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petattack"), String::valueOf(speaker->getObjectID()));
	} else if (command == GUARD) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petguard"), String::valueOf(speaker->getObjectID()), true);
	} else if (command == FRIEND) {
		enqueueOwnerOnlyPetCommand(speaker, pet, STRING_HASHCODE("petfriend"), "");
	} else if (command == FOLLOWOTHER) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petfollow"), String::valueOf(speaker->getObjectID()), false);
	} else if (command == TRICK1) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("pettrick"), "1", true);
	} else if (command == TRICK2) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("pettrick"), "2", true);
	} else if (command == PATROL) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petpatrol"), "");
	} else if (command == GETPATROLPOINT) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petgetpatrolpoint"), "", true);
	} else if (command == CLEARPATROLPOINTS) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petclearpatrolpoints"), "", true);
	} else if (command == FORMATION1) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petformation"), "wedge", true);
	} else if (command == FORMATION2) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petformation"), "column", true);
	} else if (command == SPECIAL_ATTACK1) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petspecialattack"), "1 " + String::valueOf(speaker->getObjectID()));
	} else if (command == SPECIAL_ATTACK2) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petspecialattack"), "2 " + String::valueOf(speaker->getObjectID()));
	} else if (command == RANGED_ATTACK) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petrangedattack"), "", true);
	} else if (command == GROUP) {
		enqueueOwnerOnlyPetCommand(speaker, pet, STRING_HASHCODE("petgroup"), "");
	} else if (command == RECHARGEOTHER) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petrechargeother"), "");
	} else if (command == TRANSFER) {
		enqueueOwnerOnlyPetCommand(speaker, pet, STRING_HASHCODE("pettransfer"), "");
	} else if (command == HARVEST) {
		enqueuePetCommand(speaker, pet, STRING_HASHCODE("petharvest"), String::valueOf(speaker->getObjectID()), false);
	}

	// Hand off to droid modules for handling
	if (pcd->getPetType() == PetManager::DROIDPET) {
		DroidObject* droidObject = cast<DroidObject*>(pet);
		if (droidObject != nullptr) {
			droidObject->handleChat(speaker, message);
		}
	}

	if (command > 0) {
		if (command == (FOLLOW || FOLLOWOTHER) && pet->peekBlackboard("formationOffset")) {
			pet->eraseBlackboard("formationOffset");
		}

		Locker plocker(pcd, speaker);
		pcd->setLastCommander(speaker);

		if (command != GROUP)
			pcd->setLastCommand(command);
	}
}

int PetManagerImplementation::getTrainedCommandNum(PetControlDevice* petControlDevice, const String& msg) {
	String name = petControlDevice->getCustomObjectName().toString();
	String petName = "";

	if (name.length() > 2) {
		petName = name.subString(1, name.length() - 1); // Remove parenthesis
	}

	for (int i = 0; i <= TOTALCOMMANDS; i++) {
		// Check if pet is trained in the command
		if (petControlDevice->hasTrainedCommand(i)) {
			// Check if string exactly matches registered command
			if (petControlDevice->getTrainedCommand(i) == msg)
				return i;

			// Check if string matches registered command with or without the pet's name
			if (petName != "") {
				String cmdWithName = petName + " " + petControlDevice->getTrainedCommand(i);
				if (cmdWithName == msg)
					return i;

				String msgWithName = petName + " " + msg;
				if (petControlDevice->getTrainedCommand(i) == msgWithName)
					return i;
			}
		}
	}

	return 0;
}

bool PetManagerImplementation::handleCommandTraining(CreatureObject* speaker, AiAgent* pet, const String& message) {
	if (speaker == nullptr || pet == nullptr)
		return false;

	if (message.isEmpty())
		return false;

	ManagedReference<CreatureObject*> linkedCreature = pet->getLinkedCreature().get();
	if (linkedCreature == nullptr)
		return false;

	// Only owner may train
	if (linkedCreature != speaker)
		return false;

	ManagedReference<PetControlDevice*> pcd = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (pcd == nullptr)
		return false;

	if (pcd->hasTrainedCommandString(message)) {
		if (pet->getOptionsBitmask() & OptionBitmask::CONVERSE) {
			String stf = pet->getPersonalityStf();
			StringBuffer message;
			message << stf << ":confused";
			StringIdChatParameter chat;
			chat.setStringId(message.toString());
			pet->getZoneServer()->getChatManager()->broadcastChatMessage(pet, chat, 0, 0, 0);
		} else {
			pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?"
		}
		return true;
	}

	Locker locker(pcd);

	unsigned int trainingCommand = pcd->getTrainingCommand();
	int petType = pcd->getPetType();

	// Train command
	if (petType == CREATUREPET) {
		bool alreadyTrained = pcd->hasTrainedCommand(trainingCommand);

		if (!alreadyTrained) {
			bool success = false;
			Creature* petCreature = cast<Creature*>(pet);

			if (petCreature == nullptr)
				return false;

			int skill = speaker->getSkillMod("tame_level");
			int level = petCreature->getAdultLevel();
			int roll = System::random(skill + level);

			if (skill > roll)
				success = true;

			if (!success) {
				pet->showFlyText("npc_reaction/flytext", "confused", 204, 0, 0); // "?"
				speaker->sendSystemMessage("@pet/pet_menu:pet_nolearn");		 // Your pet doesn't seem to understand you.
				return true;
			}
		}

		// Success
		pcd->addTrainedCommand(trainingCommand, message);
		pet->showFlyText("npc_reaction/flytext", "threaten", 204, 0, 0); // "!"
		speaker->sendSystemMessage("@pet/pet_menu:pet_learn");			 // You teach your pet a new command.

		if (!alreadyTrained) {
			auto creatureTemplate = pet->getCreatureTemplate();

			if (creatureTemplate == nullptr)
				return true;

			PlayerManager* playerManager = zoneServer->getPlayerManager();

			if (pet->hasPetDeed()) {
				playerManager->awardExperience(speaker, "creaturehandler", 100);
			} else {
				playerManager->awardExperience(speaker, "creaturehandler", 10 * creatureTemplate->getLevel());
			}
		}
	} else {
		pcd->addTrainedCommand(trainingCommand, message);
		if (pet->getOptionsBitmask() & OptionBitmask::CONVERSE) {
			String stf = pet->getPersonalityStf();
			StringBuffer message;
			message << stf << ":end_convo";
			StringIdChatParameter chat;
			chat.setStringId(message.toString());
			pet->getZoneServer()->getChatManager()->broadcastChatMessage(pet, chat, 0, 0, 0);
		} else {
			pet->showFlyText("npc_reaction/flytext", "threaten", 204, 0, 0); // "?"
			speaker->sendSystemMessage("@pet/pet_menu:pet_learn");			 // You teach your pet a new command.
		}
	}

	// No renaming of faction pets
	if (petType == FACTIONPET)
		return true;
	// no renaming of converse style droids with personalities installed.
	if ((pet->getOptionsBitmask() & OptionBitmask::CONVERSE) && petType == DROIDPET)
		return true;
	// Check for naming string
	StringTokenizer tokenizer(message);
	tokenizer.setDelimeter(" ");
	String parsedName = "";
	int numberOfSubStrings = 0;

	while (tokenizer.hasMoreTokens()) {
		numberOfSubStrings++;

		if (!parsedName.isEmpty())
			break;

		tokenizer.getStringToken(parsedName);
	}

	String futureName = pcd->getFutureName();
	unsigned int namingProgress = pcd->getNamingProgress();

	// Validate and check name
	if (numberOfSubStrings > 1) {
		ZoneProcessServer* zps = pet->getZoneProcessServer();
		NameManager* nameManager = zps->getNameManager();

		if (nameManager->validateName(parsedName) != NameManagerResult::ACCEPTED) {
			return true;
		}
		if (futureName == parsedName && !pcd->hasUsedNamingCommand(trainingCommand)) {
			pcd->incrementNamingProgress(trainingCommand);
		} else {
			pcd->resetNamingProgress();
			pcd->incrementNamingProgress(trainingCommand);
			pcd->setFutureName(parsedName);
			return true;
		}
	} else {
		pcd->resetNamingProgress();
		parsedName = "";
		pcd->setFutureName(parsedName);
		return true;
	}

	// Set name, if applicable
	if (pcd->getNamingProgress() == 4) {
		UnicodeString newName = "(" + futureName + ")";
		pcd->setCustomObjectName(newName, true);
		pet->setCustomObjectName(newName, true);
		pcd->resetNamingProgress();
	}

	return true;
}

void PetManagerImplementation::enqueuePetCommand(CreatureObject* player, AiAgent* pet, uint32 command, const String& args, bool selfTarget) {
	uint64 targetID;
	if (selfTarget)
		targetID = player->getObjectID();
	else
		targetID = player->getTargetID();

	// CreatureObject* pet, uint32 command, const String& args, uint64 target, int priority = -1
	EnqueuePetCommand* enqueueCommand = new EnqueuePetCommand(pet, command, args, targetID, QueueCommand::NOCOMBATQUEUE);
	enqueueCommand->schedule(50);
}

void PetManagerImplementation::enqueueOwnerOnlyPetCommand(CreatureObject* player, AiAgent* pet, uint32 command, const String& args) {
	ManagedReference<CreatureObject*> linkedCreature = pet->getLinkedCreature().get();

	if (linkedCreature == nullptr)
		return;

	// Player must be pet's owner
	if (linkedCreature != player)
		return;

	// CreatureObject* pet, uint32 command, const String& args, uint64 target, int priority = -1
	EnqueuePetCommand* enqueueCommand = new EnqueuePetCommand(pet, command, args, player->getTargetID(), QueueCommand::NOCOMBATQUEUE);
	enqueueCommand->schedule(50);
}

int PetManagerImplementation::notifyDestruction(TangibleObject* destructor, AiAgent* destructedObject, int condition, bool isCombatAction) {
	if (!destructedObject->isPet() || destructedObject->isDead() || destructedObject->isIncapacitated())
		return 1;

	if (destructedObject->isMount() && destructedObject->hasRidingCreature()) {
		Reference<CreatureObject*> rider = destructedObject->getSlottedObject("rider").castTo<CreatureObject*>();

		if (rider != nullptr) {
			Locker locker(rider);
			rider->updateCooldownTimer("mount_dismount", 0);
			rider->executeObjectControllerAction(STRING_HASHCODE("dismount"));
		}
	}

	destructor->removeDefender(destructedObject);

	ManagedReference<PetControlDevice*> petControlDevice = destructedObject->getControlDevice().get().castTo<PetControlDevice*>();

	if (!destructor->isKiller() && petControlDevice != nullptr && petControlDevice->getPetType() == CREATUREPET) {
		destructedObject->setCurrentSpeed(0);
		destructedObject->setPosture(CreaturePosture::INCAPACITATED, false);
		destructedObject->updateLocomotion();

		destructedObject->setFollowObject(nullptr);

		if (destructedObject->peekBlackboard("targetProspect"))
			destructedObject->eraseBlackboard("targetProspect");

		uint32 incapTime = calculateIncapacitationTimer(destructedObject, condition);

		Reference<Task*> oldTask = destructedObject->getPendingTask("incapacitationRecovery");

		if (oldTask != nullptr && oldTask->isScheduled()) {
			oldTask->cancel();
			destructedObject->removePendingTask("incapacitationRecovery");
		}

		bool store = false;

		if (incapTime > 240) { // store pet after 4 minutes of incap
			store = true;
			incapTime = 240;
		}

		Reference<Task*> task = new PetIncapacitationRecoverTask(destructedObject, store);
		destructedObject->addPendingTask("incapacitationRecovery", task, incapTime * 1000);

	} else {
		killPet(destructor, destructedObject, isCombatAction);
	}

	return 0;
}

uint32 PetManagerImplementation::calculateIncapacitationTimer(AiAgent* pet, int condition) {
	// Switch the sign of the value
	int32 value = -condition;

	if (value < 0)
		return 120; // 2 minute minimum recovery

	uint32 recoveryTime = (value / 5); // In seconds

	if (recoveryTime < 120)
		recoveryTime = 120; // 2 minute minimum recovery

	return recoveryTime;
}

void PetManagerImplementation::killPet(TangibleObject* attacker, AiAgent* pet, bool isCombatAction) {
	StringIdChatParameter stringId;

	if (attacker->isPlayerCreature()) {
		stringId.setStringId("base_player", "prose_target_dead");
		stringId.setTT(pet->getObjectID());
		(cast<CreatureObject*>(attacker))->sendSystemMessage(stringId);
	}

	pet->clearDots();

	pet->clearCombatState(true);
	pet->setPosture(CreaturePosture::DEAD, !isCombatAction, !isCombatAction);
	pet->setOblivious();
	pet->storeFollowObject();

	pet->updateTimeOfDeath();

	ManagedReference<AiAgent*> petAgent = pet;

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(petAgent);

		petAgent->clearBuffs(false, false);
	}, "ClearPetBuffsLambda");

	ManagedReference<PetControlDevice*> petControlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (petControlDevice != nullptr) {
		Locker locker(petControlDevice);

		petControlDevice->setLastCommandTarget(nullptr);
		petControlDevice->setLastCommand(PetManager::FOLLOW);

		if (petControlDevice->getPetType() == FACTIONPET) {
			ManagedReference<CreatureObject*> owner = zoneServer->getObject(pet->getCreatureLinkID()).castTo<CreatureObject*>();

			if (owner != nullptr) {
				Reference<PetControlDeviceStoreObjectTask*> task = new PetControlDeviceStoreObjectTask(petControlDevice, owner, true);
				task->execute();
			}

			petControlDevice->destroyObjectFromWorld(true);
			petControlDevice->destroyObjectFromDatabase(true);

		} else if (!attacker->isPlayerCreature() && !attacker->isPet()) {
			if (pet->getCooldownTimerMap() != nullptr && pet->getCooldownTimerMap()->isPast("vitalityLossCooldown")) {
				petControlDevice->setVitality(petControlDevice->getVitality() - 2);
				pet->getCooldownTimerMap()->updateToCurrentAndAddMili("vitalityLossCooldown", 300000);
			}
		}
	}

	pet->notifyObjectKillObservers(attacker);
}
