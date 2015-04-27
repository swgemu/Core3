
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/ValidMountScaleRange.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/events/PetIncapacitationRecoverTask.h"
#include "server/zone/objects/intangible/tasks/PetControlDeviceStoreObjectTask.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/tasks/EnqueuePetCommand.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/params/primitives/StringParam.h"
#include "server/chat/ChatManager.h"

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
}

void PetManagerImplementation::loadValidMountScaleRanges() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/mount/valid_scale_range.iff");

	if (iffStream == NULL) {
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

		if (range == NULL)
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
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return PetManager::INVALIDCREATURE;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return PetManager::INVALIDCREATURE;

	//Check if the pet's species is able to be trained as a mount
	if (!pet->hasSlotDescriptor("rider"))
		return PetManager::INVALIDCREATURE;

	SharedObjectTemplate* objectTemplate = petControlDevice->getObjectTemplate();
	if (objectTemplate == NULL)
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

	return NULL;
}

float PetManagerImplementation::getMountedRunSpeed(CreatureObject* mount) {
	if (!mount->isMount())
		return mount->getRunSpeed();

	ManagedReference<PetControlDevice*> pcd = mount->getControlDevice().get().castTo<PetControlDevice*>();

	if (pcd != NULL) {
		SharedObjectTemplate* objectTemplate = pcd->getObjectTemplate();

		if (objectTemplate != NULL) {
			MountSpeedData* mountSpeedData = getMountSpeedData(objectTemplate->getAppearanceFilename());

			if (mountSpeedData != NULL)
				return mountSpeedData->getRunSpeed();
		}
	}

	return mount->getRunSpeed();
}

void PetManagerImplementation::handleChat(CreatureObject* speaker, AiAgent* pet, const String& message){
	if( speaker == NULL || pet == NULL )
		return;

	if( message.isEmpty() )
		return;

	if (pet->isDead() || pet->isIncapacitated())
		return;

	ManagedReference<PetControlDevice*> pcd = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if( pcd == NULL )
		return;

	// Handle command training
	if( pcd->getTrainingCommand() > 0 ){
		bool ownerChat = handleCommandTraining( speaker, pet, message );
		if (ownerChat)
			pcd->setTrainingCommand(0); // no longer training

		return;
	}

	ManagedWeakReference< CreatureObject*> linkedCreature = pet->getLinkedCreature();
	if( linkedCreature == NULL )
		return;

	// Check if speaker has permission to command pet
	// TODO: Add check for players other than owner that are on pet's friend list
	if( linkedCreature != speaker)
		return;

	ManagedWeakReference<SceneObject*> speakerParent = speaker->getRootParent();
	ManagedWeakReference<SceneObject*> petParent = pet->getRootParent();

	// If speaker is mounted, pet must be outdoors
	if( speaker->isRidingMount() && petParent != NULL )
		return;

	// If speaker is unmounted, pet and speaker must both be outdoors or inside same building
	if( !speaker->isRidingMount() && speakerParent != petParent )
		return;

	// Handle trained command
	if( isTrainedCommand( pcd, STAY, message ) ){
		enqueuePetCommand(speaker, pet, String("petStay").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, FOLLOW, message ) ){
		enqueuePetCommand(speaker, pet, String("petFollow").toLowerCase().hashCode(), "", true);
	}
	else if( isTrainedCommand( pcd, STORE, message ) ){
		enqueueOwnerOnlyPetCommand(speaker, pet, String("petStore").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, ATTACK, message ) ){
		enqueuePetCommand(speaker, pet, String("petAttack").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, GUARD, message ) ){
		speaker->sendSystemMessage("GUARD pet command is not yet implemented.");
	}
	else if( isTrainedCommand( pcd, FRIEND, message ) ){
		speaker->sendSystemMessage("FRIEND pet command is not yet implemented.");
	}
	else if( isTrainedCommand( pcd, FOLLOWOTHER, message ) ){
		enqueuePetCommand(speaker, pet, String("petFollow").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, TRICK1, message ) ){
		enqueuePetCommand(speaker, pet, String("petTrick").toLowerCase().hashCode(), "1", true);
	}
	else if( isTrainedCommand( pcd, TRICK2, message ) ){
		enqueuePetCommand(speaker, pet, String("petTrick").toLowerCase().hashCode(), "2", true);
	}
	else if( isTrainedCommand( pcd, PATROL, message ) ){
		enqueuePetCommand(speaker, pet, String("petPatrol").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, GETPATROLPOINT, message ) ){
		enqueuePetCommand(speaker, pet, String("petGetPatrolPoint").toLowerCase().hashCode(), "", true);
	}
	else if( isTrainedCommand( pcd, CLEARPATROLPOINTS, message ) ){
		enqueuePetCommand(speaker, pet, String("petClearPatrolPoints").toLowerCase().hashCode(), "", true);
	}
	else if( isTrainedCommand( pcd, FORMATION1, message ) ){
		speaker->sendSystemMessage("FORMATION2 pet command is not yet implemented.");
	}
	else if( isTrainedCommand( pcd, FORMATION2, message ) ){
		speaker->sendSystemMessage("FORMATION2 pet command is not yet implemented.");
	}
	else if( isTrainedCommand( pcd, SPECIAL_ATTACK1, message ) ){
		enqueuePetCommand(speaker, pet, String("petSpecialAttack").toLowerCase().hashCode(), "1");
	}
	else if( isTrainedCommand( pcd, SPECIAL_ATTACK2, message ) ){
		enqueuePetCommand(speaker, pet, String("petSpecialAttack").toLowerCase().hashCode(), "2");
	}
	else if( isTrainedCommand( pcd, RANGED_ATTACK, message ) ){
		speaker->sendSystemMessage("RANGED_ATTACK pet command is not yet implemented.");
	}
	else if( isTrainedCommand( pcd, GROUP, message ) ){
		enqueueOwnerOnlyPetCommand(speaker, pet, String("petGroup").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, RECHARGEOTHER, message ) ){
		enqueuePetCommand(speaker, pet, String("petRechargeOther").toLowerCase().hashCode(), "");
	}
	else if( isTrainedCommand( pcd, TRANSFER, message ) ){
		enqueueOwnerOnlyPetCommand(speaker, pet, String("petTransfer").toLowerCase().hashCode(), "");
	}

	// Hand off to droid modules for handling
	if( pcd->getPetType() == PetManager::DROIDPET ){

		DroidObject* droidObject = cast<DroidObject*>(pet);
		if( droidObject != NULL ){
			droidObject->handleChat(speaker, message);
		}

	}

}

bool PetManagerImplementation::isTrainedCommand( PetControlDevice* petControlDevice, unsigned int commandId, const String& msg ){

	// Check if pet is trained in the command
	if( !petControlDevice->hasTrainedCommand( commandId ) )
		return false;

	// Check if string exactly matches registered command
	if( petControlDevice->getTrainedCommand(commandId) == msg )
		return true;

	// Check if string matches registered command with or without the pet's name
	String name = petControlDevice->getCustomObjectName().toString();
	if( name.length() > 2 ){

		String petName = name.subString( 1, name.length()-1 ); // Remove parenthesis

		String cmdWithName = petName + " " + petControlDevice->getTrainedCommand(commandId);
		if( cmdWithName == msg )
			return true;

		String msgWithName = petName + " " + msg;
		if( petControlDevice->getTrainedCommand(commandId) == msgWithName )
			return true;

	}

	return false;

}

bool PetManagerImplementation::handleCommandTraining(CreatureObject* speaker, AiAgent* pet, const String& message){

	if( speaker == NULL || pet == NULL )
		return false;

	if( message.isEmpty() )
		return false;

	ManagedWeakReference< CreatureObject*> linkedCreature = pet->getLinkedCreature();
	if( linkedCreature == NULL )
		return false;

	// Only owner may train
	if( linkedCreature != speaker)
		return false;

	ManagedReference<PetControlDevice*> pcd = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if( pcd == NULL )
		return false;

	if( pcd->hasTrainedCommandString(message) ){
		if (pet->getOptionsBitmask() & OptionBitmask::CONVERSE) {
			String stf = pet->getPersonalityStf();
			StringBuffer message;
			message << stf << ":confused";
			StringIdChatParameter chat;
			chat.setStringId(message.toString());
			pet->getZoneServer()->getChatManager()->broadcastMessage(pet,chat,0,0,0);
		} else {
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?"
		}
		return true;
	}

	unsigned int trainingCommand = pcd->getTrainingCommand();
	int petType = pcd->getPetType();

	// Train command
	if (petType == CREATUREPET) {
		bool alreadyTrained = pcd->hasTrainedCommand(trainingCommand);

		if (!alreadyTrained) {
			bool success = false;

			int skill = speaker->getSkillMod("tame_level");
			int roll = System::random(skill + 30);

			if (skill > roll)
				success = true;

			if (!success) {
				pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?"
				speaker->sendSystemMessage("@pet/pet_menu:pet_nolearn"); // Your pet doesn't seem to understand you.
				return true;
			}
		}

		// Success
		pcd->addTrainedCommand( trainingCommand, message );
		pet->showFlyText("npc_reaction/flytext","threaten", 204, 0, 0);  // "?"
		speaker->sendSystemMessage("@pet/pet_menu:pet_learn"); // You teach your pet a new command.

		if (!alreadyTrained) {
			CreatureTemplate* creatureTemplate = pet->getCreatureTemplate();

			if (creatureTemplate == NULL)
				return true;

			PlayerManager* playerManager = zoneServer->getPlayerManager();

			if (pet->hasPetDeed()) {
				playerManager->awardExperience(speaker, "creaturehandler", 100);
			} else {
				playerManager->awardExperience(speaker, "creaturehandler", 10 * creatureTemplate->getLevel());
			}
		}
	}
	else{
		pcd->addTrainedCommand( trainingCommand, message );
		if (pet->getOptionsBitmask() & OptionBitmask::CONVERSE) {
			String stf = pet->getPersonalityStf();
			StringBuffer message;
			message << stf << ":end_convo";
			StringIdChatParameter chat;
			chat.setStringId(message.toString());
			pet->getZoneServer()->getChatManager()->broadcastMessage(pet,chat,0,0,0);
		} else {
			pet->showFlyText("npc_reaction/flytext","threaten", 204, 0, 0);  // "?"
			speaker->sendSystemMessage("@pet/pet_menu:pet_learn"); // You teach your pet a new command.
		}
	}

	// No renaming of faction pets
	if (petType == FACTIONPET)
		return true;
	// no renaming of converse style droids with personalities installed.
	if ( (pet->getOptionsBitmask() & OptionBitmask::CONVERSE) && petType == DROIDPET )
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
		if (futureName == parsedName  && !pcd->hasUsedNamingCommand(trainingCommand)) {
			pcd->incrementNamingProgress(trainingCommand);
		}
		else {
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

void PetManagerImplementation::enqueuePetCommand(CreatureObject* player, AiAgent* pet, uint32 command, const String& args, bool selfTarget){
	uint64 targetID;
	if (selfTarget)
		targetID = player->getObjectID();
	else
		targetID = player->getTargetID();
	//CreatureObject* pet, uint32 command, const String& args, uint64 target, int priority = -1
	EnqueuePetCommand* enqueueCommand = new EnqueuePetCommand(pet, command, args, targetID, 1);
	enqueueCommand->execute();
}

void PetManagerImplementation::enqueueOwnerOnlyPetCommand(CreatureObject* player, AiAgent* pet, uint32 command, const String& args){
	ManagedReference< CreatureObject*> linkedCreature = pet->getLinkedCreature().get();
	if( linkedCreature == NULL )
		return;

	// Player must be pet's owner
	if( linkedCreature != player)
		return;

	//CreatureObject* pet, uint32 command, const String& args, uint64 target, int priority = -1
	EnqueuePetCommand* enqueueCommand = new EnqueuePetCommand(pet, command, args, player->getTargetID(), 1);
	enqueueCommand->execute();

}

int PetManagerImplementation::notifyDestruction(TangibleObject* destructor, AiAgent* destructedObject, int condition) {
	if (!destructedObject->isPet() || destructedObject->isDead() || destructedObject->isIncapacitated())
		return 1;

	if (destructedObject->isMount() && destructedObject->hasRidingCreature()) {
		Reference<CreatureObject*> rider = destructedObject->getSlottedObject("rider").castTo<CreatureObject*>();

		if (rider != NULL) {
			rider->updateCooldownTimer("mount_dismount", 0);
			rider->executeObjectControllerAction(String("dismount").hashCode());
		}
	}

	destructor->removeDefender(destructedObject);

	destructedObject->clearDots();

	ManagedReference<PetControlDevice*> petControlDevice = destructedObject->getControlDevice().get().castTo<PetControlDevice*>();

	if (!destructor->isKiller() && petControlDevice != NULL && petControlDevice->getPetType() == CREATUREPET) {
		destructedObject->setCurrentSpeed(0);
		destructedObject->setPosture(CreaturePosture::INCAPACITATED, true);
		destructedObject->updateLocomotion();

		uint32 incapTime = calculateIncapacitationTimer(destructedObject, condition);

		Reference<Task*> oldTask = destructedObject->getPendingTask("incapacitationRecovery");

		if (oldTask != NULL && oldTask->isScheduled()) {
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
		killPet(destructor, destructedObject);
	}

	return 0;
}

uint32 PetManagerImplementation::calculateIncapacitationTimer(AiAgent* pet, int condition) {
	//Switch the sign of the value
	int32 value = -condition;

	if (value < 0)
		return 120; // 2 minute minimum recovery

	uint32 recoveryTime = (value / 5); // In seconds

	if (recoveryTime < 120)
		recoveryTime = 120; // 2 minute minimum recovery

	return recoveryTime;
}

void PetManagerImplementation::killPet(TangibleObject* attacker, AiAgent* pet) {

	// TODO REMOVE AFTER TESTING
	bool attackerIsAdmin = false;
	// END REMOVE

	StringIdChatParameter stringId;

	if (attacker->isPlayerCreature()) {
		stringId.setStringId("base_player", "prose_target_dead");
		stringId.setTT(pet->getObjectID());
		(cast<CreatureObject*>(attacker))->sendSystemMessage(stringId);

		// TODO REMOVE AFTER TESTING
		//ManagedReference<PlayerObject*> ghost = (cast<CreatureObject*>(attacker))->getPlayerObject();
		//if (ghost != NULL && ghost->isPrivileged())
		//	attackerIsAdmin = true;
		// END REMOVE
	}

	pet->setCurrentSpeed(0);
	pet->clearCombatState(true);
	pet->setPosture(CreaturePosture::DEAD, true);
	pet->updateLocomotion();

	pet->updateTimeOfDeath();

	Reference<AiAgent*> petAgent = pet;

	EXECUTE_TASK_1(petAgent, {
			Locker locker(petAgent_p);

			petAgent_p->clearBuffs(false);
	});


	ManagedReference<PetControlDevice*> petControlDevice = pet->getControlDevice().get().castTo<PetControlDevice*>();

	if (petControlDevice != NULL) {

		if (petControlDevice->getPetType() == FACTIONPET) {
			ManagedReference<CreatureObject*> owner = zoneServer->getObject(pet->getCreatureLinkID()).castTo<CreatureObject*>();

			if (owner != NULL) {
				Reference<PetControlDeviceStoreObjectTask*> task = new PetControlDeviceStoreObjectTask(petControlDevice, owner, true);
				task->execute();
			}

			Locker locker(petControlDevice);

			petControlDevice->destroyObjectFromWorld(true);
			petControlDevice->destroyObjectFromDatabase(true);

		} else if ( (!attacker->isPlayerCreature() && !attacker->isPet()) || attackerIsAdmin) { // TODO REMOVE attackerIsAdmin AFTER TESTING

			if (pet->getCooldownTimerMap() != NULL && pet->getCooldownTimerMap()->isPast("vitalityLossCooldown")) {

				petControlDevice->setVitality(petControlDevice->getVitality() - 2);
				pet->getCooldownTimerMap()->updateToCurrentAndAddMili("vitalityLossCooldown", 300000);
			}
		}

	}

	pet->notifyObjectKillObservers(attacker);

}
