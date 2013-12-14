#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/PetControlObserver.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "tasks/CallPetTask.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/DroidPowerTask.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "tasks/StorePetTask.h"

void PetControlDeviceImplementation::callObject(CreatureObject* player) {
	if (player->isInCombat() || player->isDead() || player->isIncapacitated() || player->getPendingTask("tame_pet") != NULL) {
		player->sendSystemMessage("@pet/pet_menu:cant_call"); // You cannot call this pet right now.
		return;
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("@pet/pet_menu:mounted_call_warning"); // You cannot call a pet while mounted or riding a vehicle.
		return;
	}

	if (player->getParent() != NULL) {
		ManagedReference<SceneObject*> strongRef = player->getParentRecursively(SceneObjectType::BUILDING);
		ManagedReference<BuildingObject*> building;

		if (strongRef != NULL)
			building = strongRef.castTo<BuildingObject*>();

		if (building == NULL || building->isPrivateStructure()) {
			player->sendSystemMessage("@pet/pet_menu:private_house"); // You cannot call pets in a private building.
			return;
		}
	}

	if (!isASubChildOf(player))
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost->hasActivePet(pet))
		return;

	if (vitality <= 0) {
		player->sendSystemMessage("@pet/pet_menu:dead_pet"); // This pet is dead. Select DESTROY from the radial menu to delete this pet control device.
		return;
	}

	unsigned int petFaction = pet->getFaction();

	if (petFaction != 0) {
		if (player->getFaction() == 0) {
			StringIdChatParameter message("@faction_perk:prose_be_declared"); // You must be declared to a faction to use %TT.
			message.setTT(pet->getDisplayedName());
			player->sendSystemMessage(message);
			return;
		}

		if (player->getFaction() != petFaction || ghost->getFactionStatus() == FactionStatus::ONLEAVE) {
			StringIdChatParameter message("@faction_perk:prose_be_declared_faction"); // You must be a declared %TO to use %TT.
			message.setTO(pet->getFactionString());
			message.setTT(pet->getDisplayedName());
			player->sendSystemMessage(message);
			return;
		}
	}

	if(player->getPendingTask("call_pet") != NULL) {
		StringIdChatParameter waitTime("pet/pet_menu", "call_delay_finish_pet"); // Already calling a Pet: Call will be finished in %DI seconds.
		Time nextExecution;
		Core::getTaskManager()->getNextExecutionTime(player->getPendingTask("call_pet"), nextExecution);
		int timeLeft = (nextExecution.getMiliTime() / 1000) - System::getTime();
		waitTime.setDI(timeLeft);

		player->sendSystemMessage(waitTime);
		return;
	}

	growPet();

	int currentlySpawned = 0;
	int spawnedLevel = 0;
	int maxPets = 1;
	int maxLevelofPets = 10;
	int level = pet->getLevel();

	if (petType == CREATUREPET) {
		bool ch = player->hasSkill("outdoors_creaturehandler_novice");

		if (ch) {
			maxPets = player->getSkillMod("keep_creature");
			maxLevelofPets = player->getSkillMod("tame_level");
		}

		if (level > maxLevelofPets) {
			player->sendSystemMessage("@pet/pet_menu:control_exceeded"); // Calling this pet would exceed your Control Level ability.
			return;
		}

		if (pet->isAggressiveTo(player) && (player->getSkillMod("tame_aggro") <= 0 || !ch)) {
			player->sendSystemMessage("@pet/pet_menu:lack_skill"); // You lack the skill to call a pet of this type.
			return;
		}

	} else if (petType == FACTIONPET){
		maxPets = 3;
	}

	for (int i = 0; i < ghost->getActivePetsSize(); ++i) {
		ManagedReference<AiAgent*> object = ghost->getActivePet(i);

		if (object != NULL) {
			if (object->isCreature() && petType == CREATUREPET) {
				if (++currentlySpawned >= maxPets) {
					player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
					return;
				}

				spawnedLevel += object->getLevel();

				if ((spawnedLevel + level) > maxLevelofPets) {
					player->sendSystemMessage("@pet/pet_menu:control_exceeded"); // Calling this pet would exceed your Control Level ability.
					return;
				}
			} else if (object->isNonPlayerCreatureObject() && petType == FACTIONPET) {
				if (++currentlySpawned >= maxPets) {
					player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
					return;
				}
			} else if (object->isDroidObject() && petType == DROIDPET) {
				if (++currentlySpawned >= maxPets) {
					player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
					return;
				}
			}

		}
	}

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer != NULL) {
		server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(player);
	}

	if(player->getCurrentCamp() == NULL && player->getCityRegion() == NULL) {

		Reference<CallPetTask*> callPet = new CallPetTask(_this.get(), player, "call_pet");

		StringIdChatParameter message("pet/pet_menu", "call_pet_delay"); // Calling pet in %DI seconds. Combat will terminate pet call.
		message.setDI(15);
		player->sendSystemMessage(message);

		player->addPendingTask("call_pet", callPet, 15 * 1000);

		if (petControlObserver == NULL) {
			petControlObserver = new PetControlObserver(_this.get());
			petControlObserver->deploy();
		}

		player->registerObserver(ObserverEventType::STARTCOMBAT, petControlObserver);

	} else {

		Locker clocker(controlledObject, player);
		spawnObject(player);
	}

}

void PetControlDeviceImplementation::spawnObject(CreatureObject* player) {
	ZoneServer* zoneServer = getZoneServer();

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL)
		return;

	if (!isASubChildOf(player))
		return;

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer != NULL) {
		server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(player);
	}

	controlledObject->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
	ManagedReference<CreatureObject*> creature = NULL;

	if (controlledObject->isCreatureObject()) {
		creature = cast<CreatureObject*>(controlledObject.get());
		creature->setCreatureLink(player);
		creature->setControlDevice(_this.get());
		creature->setFaction(player->getFaction());
		creature->setObjectMenuComponent("PetMenuComponent");

		if (player->getPvpStatusBitmask() & CreatureFlag::PLAYER)
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask() - CreatureFlag::PLAYER, true);
		else
			creature->setPvpStatusBitmask(player->getPvpStatusBitmask(), true);
	}

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	ManagedReference<SceneObject*> parent = player->getParent();

	if (parent != NULL && parent->isCellObject())
		parent->transferObject(controlledObject, -1, true);
	else
		zone->transferObject(controlledObject, -1, true);

	updateStatus(1);

	if (petControlObserver != NULL)
		player->dropObserver(ObserverEventType::STARTCOMBAT, petControlObserver);

	AiAgent* pet = cast<AiAgent*>(creature.get());

	if (pet == NULL)
		return;

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	ghost->addToActivePets(pet);

	if (pet->isDroidObject()) {
		DroidObject* droid = cast<DroidObject*>(pet);

		if( droid == NULL )
			return;

		// Sanity check that there isn't another power task outstanding
		droid->removePendingTask( "droid_power" );

		// Submit new power task
		Reference<Task*> droidPowerTask = new DroidPowerTask( droid );
		droid->addPendingTask("droid_power", droidPowerTask, 60000); // 60 secs

		if( droid->hasPower() ){
			// TODO Temporarily set to autofollow player
			droid->setFollowObject(player);
		}
		else{
			droid->handleLowPower();
		}

	} else {
		pet->setFollowObject(player);
	}

	// Not training any commands
	trainingCommand = 0;


}

void PetControlDeviceImplementation::cancelSpawnObject(CreatureObject* player) {

	Reference<Task*> petTask = player->getPendingTask("call_pet");
	if(petTask) {
		petTask->cancel();
		player->removePendingTask("call_pet");
	}

	if (petControlObserver != NULL)
		player->dropObserver(ObserverEventType::STARTCOMBAT, petControlObserver);
}

void PetControlDeviceImplementation::storeObject(CreatureObject* player, bool force) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());

	if (!force && pet->isInCombat())
		return;

	if (player->isRidingMount() && player->getParent() == pet) {

		if (!force && !player->checkCooldownRecovery("mount_dismount"))
			return;

		player->executeObjectControllerAction(String("dismount").hashCode());

		if (player->isRidingMount())
			return;
	}


	// Not training any commands
	trainingCommand = 0;

	updateStatus(0);

	StorePetTask* task = new StorePetTask(player, pet);
	task->execute();
}

void PetControlDeviceImplementation::growPet() {
	if (petType != CREATUREPET)
		return;

	if (growthStage <= 0 || growthStage >= 10)
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL || !controlledObject->isCreature())
		return;

	ManagedReference<Creature*> pet = cast<Creature*>(controlledObject.get());

	ManagedReference<CreatureTemplate*> creatureTemplate = pet->getCreatureTemplate();

	if (creatureTemplate == NULL)
		return;

	Time currentTime;
	uint32 timeDelta = currentTime.getTime() - lastGrowth.getTime();
	int stagesToGrow = timeDelta / 3600; // 1 hour, for testing. TODO: Change to correct frequency (12h)

	if (stagesToGrow == 0)
		return;

	int newStage = growthStage + stagesToGrow;
	if (newStage > 10)
		newStage = 10;

	int newLevel = ((float)creatureTemplate->getLevel() / 10) * (float)newStage;
	if (newLevel < 1)
		newLevel = 1;

	pet->setHeight(creatureTemplate->getScale() * (0.5 + (newStage * 0.05)), false);
	pet->setPetLevel(newLevel);

	growthStage = newStage;
	lastGrowth.updateToCurrentTime();
}

void PetControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject != NULL) {
		Locker locker(controlledObject);

		ManagedReference<CreatureObject*> object = controlledObject->getSlottedObject("rider").castTo<CreatureObject*>();

		if (object != NULL) {
			Locker clocker(object, controlledObject);

			object->executeObjectControllerAction(String("dismount").hashCode());

			object = controlledObject->getSlottedObject("rider").castTo<CreatureObject*>();

			if (object != NULL) {
				controlledObject->removeObject(object, NULL, true);

				Zone* zone = getZone();

				if (zone != NULL)
					zone->transferObject(object, -1, false);
			}
		}

		controlledObject->destroyObjectFromDatabase(true);
	}

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

int PetControlDeviceImplementation::canBeDestroyed(CreatureObject* player) {
	ManagedReference<AiAgent*> controlledObject = cast<AiAgent*>(this->controlledObject.get().get());

	if (controlledObject != NULL) {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		if (ghost->hasActivePet(controlledObject))
			return 1;
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

bool PetControlDeviceImplementation::canBeTradedTo(CreatureObject* player, CreatureObject* receiver, int numberInTrade) {
	ManagedReference<SceneObject*> datapad = receiver->getSlottedObject("datapad");

	if (datapad == NULL)
		return false;

	if (petType == FACTIONPET) {
		player->sendSystemMessage("@pet/pet_menu:bad_type"); // You cannot trade a pet of that type. Transfer failed.
		return false;
	} else if (petType == DROIDPET) {
		int droidsInDatapad = numberInTrade;

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != NULL && obj->isPetControlDevice() ){
				Reference<PetControlDevice*> petDevice = cast<PetControlDevice*>(obj.get());
				if( petDevice != NULL && petDevice->getPetType() == PetControlDevice::DROIDPET){
					droidsInDatapad++;
				}
			}
		}

		if( droidsInDatapad >= 5){
			player->sendSystemMessage("That person has too many droids in their datapad");
			return false;
		}

		return true;

	} else if (petType == CREATUREPET) {
		ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

		if (controlledObject == NULL || !controlledObject->isAiAgent())
			return false;

		ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());

		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int numberStored = numberInTrade;
		int maxStoredPets = playerManager->getBaseStoredPets();
		int maxLevelofPets = 10;
		int level = pet->getLevel();
		bool ch = receiver->hasSkill("outdoors_creaturehandler_novice");

		if (ch) {
			maxStoredPets += receiver->getSkillMod("stored_pets");
			maxLevelofPets = receiver->getSkillMod("tame_level");
		}

		if (level > maxLevelofPets) {
			player->sendSystemMessage("@pet/pet_menu:no_chance"); // That person has no chance of controlling this creature. Transfer failed.
			return false;
		}

		if (pet->isAggressiveTo(receiver) && (receiver->getSkillMod("tame_aggro") <= 0 || !ch)) {
			player->sendSystemMessage("@pet/pet_menu:no_chance"); // That person has no chance of controlling this creature. Transfer failed.
			return false;
		}

		for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

			if (object != NULL && object->isPetControlDevice()) {
				PetControlDevice* device = cast<PetControlDevice*>( object.get());

				if (device->getPetType() == PetControlDevice::CREATUREPET) {
					if (++numberStored >= maxStoredPets) {
						player->sendSystemMessage("@pet/pet_menu:targ_too_many_stored"); // That person has too many stored pets. Transfer failed.
						receiver->sendSystemMessage("@pet/pet_menu:sys_too_many_stored"); // There are too many pets stored in this container. Release some of them to make room for more.
						return false;
					}

				}
			}
		}

		return true;
	}

	return false;
}

void PetControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	if (petType == DROIDPET) {
		ManagedReference<DroidObject*> droid = this->controlledObject.get().castTo<DroidObject*>();

		if (droid != NULL) {
			droid->fillAttributeList(alm, object);
		}
	} else {
		ManagedReference<AiAgent*> pet = cast<AiAgent*>(this->controlledObject.get().get());

		if (pet != NULL) {
			alm->insertAttribute("challenge_level", pet->getLevel());

			if (petType == CREATUREPET)
				alm->insertAttribute("creature_vitality", String::valueOf(vitality) + "/" + String::valueOf(maxVitality));

			alm->insertAttribute("creature_health", pet->getBaseHAM(0));
			alm->insertAttribute("creature_action", pet->getBaseHAM(3));
			alm->insertAttribute("creature_mind", pet->getBaseHAM(6));

			int armor = pet->getArmor();
			if (armor == 0)
				alm->insertAttribute("armor_rating", "None");
			else if (armor == 1)
				alm->insertAttribute("armor_rating", "Light");
			else if (armor == 2)
				alm->insertAttribute("armor_rating", "Medium");
			else if (armor == 3)
				alm->insertAttribute("armor_rating", "Heavy");

			if (pet->getKinetic() < 0)
				alm->insertAttribute("dna_comp_armor_kinetic", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_kinetic", pet->getKinetic());

			if (pet->getEnergy() < 0)
				alm->insertAttribute("dna_comp_armor_energy", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_energy", pet->getEnergy());

			if (pet->getBlast() < 0)
				alm->insertAttribute("dna_comp_armor_blast", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_blast", pet->getBlast());

			if (pet->getHeat() < 0)
				alm->insertAttribute("dna_comp_armor_heat", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_heat", pet->getHeat());

			if (pet->getCold() < 0)
				alm->insertAttribute("dna_comp_armor_cold", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_cold", pet->getCold());

			if (pet->getElectricity() < 0)
				alm->insertAttribute("dna_comp_armor_electric", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_electric", pet->getElectricity());

			if (pet->getAcid() < 0)
				alm->insertAttribute("dna_comp_armor_acid", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_acid", pet->getAcid());

			if (pet->getStun() < 0)
				alm->insertAttribute("dna_comp_armor_stun", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_stun", pet->getStun());

			if (pet->getLightSaber() < 0)
				alm->insertAttribute("dna_comp_armor_saber", "Vulnerable");
			else
				alm->insertAttribute("dna_comp_armor_saber", pet->getLightSaber());

			ManagedReference<WeaponObject*> weapon = pet->getWeapon();
			if (weapon != NULL)
				alm->insertAttribute("creature_attack", weapon->getAttackSpeed());

			alm->insertAttribute("creature_tohit", pet->getChanceHit());
			alm->insertAttribute("creature_damage", String::valueOf(pet->getDamageMin()) + " - " + String::valueOf(pet->getDamageMax()));

			if (petType == CREATUREPET) {
				CreatureAttackMap* attMap = pet->getAttackMap();
				if (attMap->size() > 0) {
					String str = StringIdManager::instance()->getStringId(("@combat_effects:" + pet->getAttackMap()->getCommand(0)).hashCode()).toString();
					alm->insertAttribute("spec_atk_1", str);
				} else
					alm->insertAttribute("spec_atk_1", " ---");

				if (attMap->size() > 1) {
					String str = StringIdManager::instance()->getStringId(("@combat_effects:" + pet->getAttackMap()->getCommand(1)).hashCode()).toString();
					alm->insertAttribute("spec_atk_2", str);
				} else
					alm->insertAttribute("spec_atk_2", " ---");

				CreatureTemplate* creatureTemplate = pet->getCreatureTemplate();
				if (creatureTemplate != NULL) {
					if (creatureTemplate->getWeapons().size() > 0)
						alm->insertAttribute("dna_comp_ranged_attack", "Yes");
					else
						alm->insertAttribute("dna_comp_ranged_attack", "No");
				} else
					alm->insertAttribute("dna_comp_ranged_attack", "No");
			}
		}
	}

	// Trained Commands
	if ( trainedCommands.size() > 0) {
		alm->insertAttribute("pet_command", "" );
	}

	if( trainedCommands.contains(STAY) ){
		alm->insertAttribute("pet_command_1", trainedCommands.get(STAY) );
	}

	if( trainedCommands.contains(FOLLOW) ){
		alm->insertAttribute("pet_command_0", trainedCommands.get(FOLLOW) );
	}

	if( trainedCommands.contains(STORE) ){
		alm->insertAttribute("pet_command_11", trainedCommands.get(STORE) );
	}

	if( trainedCommands.contains(ATTACK) ){
		alm->insertAttribute("pet_command_4", trainedCommands.get(ATTACK) );
	}

	if( trainedCommands.contains(GUARD) ){
		alm->insertAttribute("pet_command_2", trainedCommands.get(GUARD) );
	}

	if( trainedCommands.contains(FRIEND) ){
		alm->insertAttribute("pet_command_3", trainedCommands.get(FRIEND) );
	}

	if( trainedCommands.contains(FOLLOWOTHER) ){
		alm->insertAttribute("pet_command_17", trainedCommands.get(FOLLOWOTHER) );
	}

	if( trainedCommands.contains(TRICK1) ){
		alm->insertAttribute("pet_command_12", trainedCommands.get(TRICK1) );
	}

	if( trainedCommands.contains(TRICK2) ){
		alm->insertAttribute("pet_command_13", trainedCommands.get(TRICK2) );
	}

	if( trainedCommands.contains(PATROL) ){
		alm->insertAttribute("pet_command_5", trainedCommands.get(PATROL) );
	}

	if( trainedCommands.contains(FORMATION1) ){
		alm->insertAttribute("pet_command_8", trainedCommands.get(FORMATION1) );
	}

	if( trainedCommands.contains(FORMATION2) ){
		alm->insertAttribute("pet_command_9", trainedCommands.get(FORMATION2) );
	}

	if( trainedCommands.contains(SPECIAL_ATTACK1) ){
		alm->insertAttribute("pet_command_18", trainedCommands.get(SPECIAL_ATTACK1) );
	}

	if( trainedCommands.contains(SPECIAL_ATTACK2) ){
		alm->insertAttribute("pet_command_19", trainedCommands.get(SPECIAL_ATTACK2) );
	}

	if( trainedCommands.contains(RANGED_ATTACK) ){
		alm->insertAttribute("pet_command_20", trainedCommands.get(RANGED_ATTACK) );
	}

	if( trainedCommands.contains(GROUP) ){
		alm->insertAttribute("pet_command_16", trainedCommands.get(GROUP) );
	}

	if( trainedCommands.contains(RECHARGEOTHER) ){
		alm->insertAttribute("@pet/pet_menu:menu_recharge_other", trainedCommands.get(RECHARGEOTHER) );
	}

}

void PetControlDeviceImplementation::handleChat(CreatureObject* speaker, const String& message){

	// Handle command training
	if( trainingCommand > 0 ){
		handleCommandTraining( speaker, message );
		trainingCommand = 0; // no longer training
		return;
	}

	if( speaker == NULL )
		return;

	if( message.isEmpty() )
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	ManagedWeakReference< CreatureObject*> linkedCreature = pet->getLinkedCreature();
	if( linkedCreature == NULL )
		return;

	// Check if speaker has permission to command pet
	// TODO: Add check for players other than owner that are on pet's friend list
	if( linkedCreature != speaker)
		return;

	// Handle trained command
	if( trainedCommands.contains(STAY) && trainedCommands.get(STAY) == message ){
		stay( speaker );
	}
	else if( trainedCommands.contains(FOLLOW) && trainedCommands.get(FOLLOW) == message ){
		follow( speaker );
	}
	else if( trainedCommands.contains(STORE) && trainedCommands.get(STORE) == message ){
		storeObject( linkedCreature.get() ); // storeObject expects pet owner to be passed
	}
	else if( trainedCommands.contains(ATTACK) && trainedCommands.get(ATTACK) == message ){
		speaker->sendSystemMessage("ATTACK pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(GUARD) && trainedCommands.get(GUARD) == message ){
		speaker->sendSystemMessage("GUARD pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(FRIEND) && trainedCommands.get(FRIEND) == message ){
		speaker->sendSystemMessage("FRIEND pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(FOLLOWOTHER) && trainedCommands.get(FOLLOWOTHER) == message ){
		followOther(speaker);
	}
	else if( trainedCommands.contains(TRICK1) && trainedCommands.get(TRICK1) == message ){
		trick1(speaker);
	}
	else if( trainedCommands.contains(TRICK2) && trainedCommands.get(TRICK2) == message ){
		trick2(speaker);
	}
	else if( trainedCommands.contains(PATROL) && trainedCommands.get(PATROL) == message ){
		speaker->sendSystemMessage("PATROL pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(FORMATION1) && trainedCommands.get(FORMATION1) == message ){
		speaker->sendSystemMessage("FORMATION2 pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(FORMATION2) && trainedCommands.get(FORMATION2) == message ){
		speaker->sendSystemMessage("FORMATION2 pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(SPECIAL_ATTACK1) && trainedCommands.get(SPECIAL_ATTACK1) == message ){
		speaker->sendSystemMessage("SPECIAL_ATTACK1 pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(SPECIAL_ATTACK2) && trainedCommands.get(SPECIAL_ATTACK2) == message ){
		speaker->sendSystemMessage("SPECIAL_ATTACK2 pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(RANGED_ATTACK) && trainedCommands.get(RANGED_ATTACK) == message ){
		speaker->sendSystemMessage("RANGED_ATTACK pet command is not yet implemented.");
	}
	else if( trainedCommands.contains(GROUP) && trainedCommands.get(GROUP) == message ){
		group(speaker);
	}
	else if( trainedCommands.contains(RECHARGEOTHER) && trainedCommands.get(RECHARGEOTHER) == message ){
		rechargeOther(speaker);
	}

}

void PetControlDeviceImplementation::handleCommandTraining(CreatureObject* speaker, const String& message){

	if( speaker == NULL )
		return;

	if( message.isEmpty() )
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	ManagedWeakReference< CreatureObject*> linkedCreature = pet->getLinkedCreature();
	if( linkedCreature == NULL )
		return;

	// Only owner may train
	if( linkedCreature != speaker)
		return;

	// Check if command string already exists
	for( int i = 0; i < trainedCommands.size(); i++ ){
		if( trainedCommands.get(i) == message ){
			pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
			return;
		}
	}

	// Train command
	if (petType == CREATUREPET) {
		bool alreadyTrained = trainedCommands.contains(trainingCommand);

		if (!alreadyTrained) {
			bool success = false;

			int skill = speaker->getSkillMod("tame_level");
			int roll = System::random(skill + 30);

			if (skill > roll)
				success = true;

			if (!success) {
				pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
				speaker->sendSystemMessage("@pet/pet_menu:pet_nolearn"); // Your pet doesn't seem to understand you.
				return;
			}
		}

		// Success
		trainedCommands.put( trainingCommand, message );
		pet->showFlyText("npc_reaction/flytext","threaten", 204, 0, 0);  // "!"
		speaker->sendSystemMessage("@pet/pet_menu:pet_learn"); // You teach your pet a new command.

		if (!alreadyTrained) {
			CreatureTemplate* creatureTemplate = pet->getCreatureTemplate();

			if (creatureTemplate == NULL)
				return;

			ZoneServer* zoneServer = speaker->getZoneServer();
			PlayerManager* playerManager = zoneServer->getPlayerManager();
			playerManager->awardExperience(speaker, "creaturehandler", 10 * creatureTemplate->getLevel());
		}
	}
	else{
		trainedCommands.put( trainingCommand, message );
		pet->showFlyText("npc_reaction/flytext","threaten", 204, 0, 0);  // "!"
		speaker->sendSystemMessage("@pet/pet_menu:pet_learn"); // You teach your pet a new command.
	}

	// No renaming of faction pets
	if (petType == FACTIONPET)
		return;

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

	// Validate and check name
	if (numberOfSubStrings > 1) {
		ZoneProcessServer* zps = pet->getZoneProcessServer();
		NameManager* nameManager = zps->getNameManager();

		if (nameManager->validateName(parsedName, -1) != NameManagerResult::ACCEPTED) {
			return;
		}

		if (futureName == parsedName)
			namingProgress++;
		else {
			namingProgress = 1;
			futureName = parsedName;
			return;
		}
	} else {
		namingProgress = 0;
		futureName = "";
		return;
	}

	// Set name, if applicable
	if (namingProgress == 4) {
		UnicodeString newName = "(" + futureName + ")";
		setCustomObjectName(newName, true);
		pet->setCustomObjectName(newName, true);
	}

}

void PetControlDeviceImplementation::setDefaultCommands(){

	trainedCommands.put(STAY, "stay");
	trainedCommands.put(FOLLOW, "follow");
	trainedCommands.put(STORE, "store");
	trainedCommands.put(ATTACK, "attack");
	trainedCommands.put(GUARD, "guard");
	trainedCommands.put(FRIEND, "friend");
	trainedCommands.put(FOLLOWOTHER, "followother");
	trainedCommands.put(PATROL, "patrol");
	trainedCommands.put(FORMATION1, "formation1");
	trainedCommands.put(FORMATION2, "formation2");
	trainedCommands.put(RANGED_ATTACK, "ranged attack");
	trainedCommands.put(GROUP, "group");

}

void PetControlDeviceImplementation::setTrainingCommand( unsigned int commandID ){

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	AiAgent* pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	// Check power on droids
	if( petType == DROIDPET) {
		ManagedReference<DroidObject*> droid = this->controlledObject.get().castTo<DroidObject*>();
		if (droid == NULL)
			return;

		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return;
		}
	}

	trainingCommand = commandID;
	pet->showFlyText("npc_reaction/flytext","alert", 204, 0, 0);  // "?"

}

void PetControlDeviceImplementation::follow(CreatureObject* player){

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	AiAgent* pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	// Check if droid has power
	if( petType == DROIDPET ){
		DroidObject* droidPet = cast<DroidObject*>(pet);
		if( droidPet == NULL )
			return;

		if( !droidPet->hasPower() ){
			pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return;
		}
	}

	pet->setFollowObject(player);

}

void PetControlDeviceImplementation::followOther(CreatureObject* player){

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	AiAgent* pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();
	if (server == NULL)
		return;

	// Target must be a player
	Reference<SceneObject*> target = server->getObject(targetID, true).castTo<SceneObject*>();
	if (target == NULL || !target->isPlayerCreature() ) {
		pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
		return;
	}

	// Check if droid has power
	if( petType == DROIDPET ){
		DroidObject* droidPet = cast<DroidObject*>(pet);
		if( droidPet == NULL )
			return;

		if( !droidPet->hasPower() ){
			pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return;
		}
	}

	pet->setFollowObject(target);

}

void PetControlDeviceImplementation::group(CreatureObject* player) {

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	ManagedReference<GroupObject*> group = pet->getGroup();
	if (group == NULL)
		GroupManager::instance()->inviteToGroup(player, pet);
	else
		GroupManager::instance()->leaveGroup(group, pet);
}

void PetControlDeviceImplementation::stay(CreatureObject* player){

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	pet->setOblivious();
}

void PetControlDeviceImplementation::rechargeOther(CreatureObject* player){

	// Droid specific command
	if( petType != DROIDPET )
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	AiAgent* pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	uint64 targetID = player->getTargetID();
	ZoneServer* server = player->getZoneServer();
	if (server == NULL)
		return;

	// Target must be a droid
	Reference<DroidObject*> target = server->getObject(targetID, true).castTo<DroidObject*>();
	if (target == NULL || !target->isDroidObject() ) {
		pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
		return;
	}

	DroidObject* droidPet = cast<DroidObject*>(pet);
	if( droidPet == NULL )
		return;

	// Check range between droids
	if (!droidPet->isInRange(target, 30.0f)){ // Same range as auto-repair
		pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
		return;
	}

	// Target can't be this droid
	if (droidPet == target ) {
		pet->showFlyText("npc_reaction/flytext","confused", 204, 0, 0);  // "?!!?!?!"
		return;
	}

	// Check if droid has power
	if( !droidPet->hasPower() ){
		pet->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
		return;
	}

	// Recharge other droid
	Locker clocker(target, player);
	droidPet->rechargeOtherDroid( target );

}

void PetControlDeviceImplementation::trick1(CreatureObject* player){

	// Creature specific command
	if( petType != CREATUREPET )
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	if( pet->getCooldownTimerMap() == NULL )
		return;

	// Check pet states
	if( pet->isInCombat() || pet->isDead() || pet->isIncapacitated() )
		return;

	// Check cooldown (single cooldown for both tricks as we can't animate both at once)
	if( !pet->getCooldownTimerMap()->isPast("trickCooldown") )
		return;

	// Heal 10% of base in wounds
	int mindHeal = pet->getBaseHAM(CreatureAttribute::MIND) * 0.10;
	int focusHeal = pet->getBaseHAM(CreatureAttribute::FOCUS) * 0.10;
	int willHeal = pet->getBaseHAM(CreatureAttribute::WILLPOWER) * 0.10;
	int shockHeal = 100;

	pet->addWounds(CreatureAttribute::MIND, -mindHeal);
	pet->addWounds(CreatureAttribute::FOCUS, -focusHeal);
	pet->addWounds(CreatureAttribute::WILLPOWER, -willHeal);
	pet->addShockWounds(-shockHeal);

	// Perform trick animation
	pet->doAnimation("trick_1");

	// Set cooldown
	pet->getCooldownTimerMap()->updateToCurrentAndAddMili("trickCooldown", 5000); // 5 sec

}

void PetControlDeviceImplementation::trick2(CreatureObject* player){

	// Creature specific command
	if( petType != CREATUREPET )
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());
	if( pet == NULL )
		return;

	if( pet->getCooldownTimerMap() == NULL )
		return;

	// Check pet states
	if( pet->isInCombat() || pet->isDead() || pet->isIncapacitated() )
		return;

	// Check cooldown (single cooldown for both tricks as we can't animate both at once)
	if( !pet->getCooldownTimerMap()->isPast("trickCooldown") )
		return;

	// Heal 20% of base in wounds
	int mindHeal = pet->getBaseHAM(CreatureAttribute::MIND) * 0.20;
	int focusHeal = pet->getBaseHAM(CreatureAttribute::FOCUS) * 0.20;
	int willHeal = pet->getBaseHAM(CreatureAttribute::WILLPOWER) * 0.20;
	int shockHeal = 200;

	pet->addWounds(CreatureAttribute::MIND, -mindHeal);
	pet->addWounds(CreatureAttribute::FOCUS, -focusHeal);
	pet->addWounds(CreatureAttribute::WILLPOWER, -willHeal);
	pet->addShockWounds(-shockHeal);

	// Perform trick animation
	pet->doAnimation("trick_2");

	// Set cooldown
	pet->getCooldownTimerMap()->updateToCurrentAndAddMili("trickCooldown", 5000); // 5 sec

}
