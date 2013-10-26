#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/intangible/PetControlObserver.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "tasks/CallPetTask.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/managers/player/PlayerManager.h"


void PetControlDeviceImplementation::callObject(CreatureObject* player) {
	if (player->getParent() != NULL)
		return;

	if (!isASubChildOf(player))
		return;

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL)
		return;

	if (controlledObject->isInQuadTree())
		return;

	if (player->isInCombat() || player->isDead() || player->isIncapacitated()) {
		player->sendSystemMessage("@pet/pet_menu:cant_call"); // You cannot call this pet right now.
		return;
	}

	if (player->isRidingMount()) {
		player->sendSystemMessage("@pet/pet_menu:mounted_call_warning"); // You cannot call a pet while mounted or riding a vehicle.
		return;
	}

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer != NULL) {
		server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(player);
	}

	if (vitality <= 0) {
		player->sendSystemMessage("@pet/pet_menu:dead_pet"); // This pet is dead. Select DESTROY from the radial menu to delete this pet control device.
		return;
	}

	if (!controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());

	unsigned int petFaction = pet->getFaction();

	if (petFaction != 0) {
		if (player->getFaction() == 0) {
			StringIdChatParameter message("@faction_perk:prose_be_declared"); // You must be declared to a faction to use %TT.
			message.setTT(pet->getDisplayedName());
			player->sendSystemMessage(message);
			return;
		}

		PlayerObject* ghost = player->getPlayerObject();
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

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL)
		return;

	int currentlySpawned = 0;
	int spawnedLevel = 0;
	int maxPets = 1;
	int maxLevelofPets = player->getSkillMod("tame_level");
	int level = pet->getLevel();

	String petType;

	if (pet->isCreature()) {
		if (player->hasSkill("outdoors_creaturehandler_novice")) {
			maxPets = player->getSkillMod("keep_creature");
		}

		petType = "creature";
	} else if (pet->isNonPlayerCreatureObject()){
		maxPets = 3;
		petType = "npc";
	}

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isPetControlDevice()) {
			PetControlDevice* device = cast<PetControlDevice*>( object.get());

			ManagedReference<AiAgent*> object = cast<AiAgent*>(device->getControlledObject());

			if (object != NULL && object->isInQuadTree()) {
				if (object->isCreature() && petType == "creature") {
					if (++currentlySpawned >= maxPets) {
						player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
						return;
					}

					spawnedLevel += object->getLevel();

					if ((spawnedLevel + level) > maxLevelofPets) {
						player->sendSystemMessage("@pet/pet_menu:control_exceeded"); // Calling this pet would exceed your Control Level ability.
						return;
					}
				} else if (object->isNonPlayerCreatureObject() && petType == "npc") {
					if (++currentlySpawned >= maxPets) {
						player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
						return;
					}
				}

			}
		}
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
		creature->setPvpStatusBitmask(player->getPvpStatusBitmask() - CreatureFlag::PLAYER, true);
		creature->setObjectMenuComponent("PetMenuComponent");
	}

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	zone->transferObject(controlledObject, -1, true);

	updateStatus(1);

	if (petControlObserver != NULL)
		player->dropObserver(ObserverEventType::STARTCOMBAT, petControlObserver);

	AiAgent* pet = cast<AiAgent*>(creature.get());

	if (pet != NULL)
		pet->setFollowObject(player);
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

void PetControlDeviceImplementation::storeObject(CreatureObject* player) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL || !controlledObject->isAiAgent())
		return;

	ManagedReference<AiAgent*> pet = cast<AiAgent*>(controlledObject.get());

	if (pet->isInCombat())
		return;

	if (player->isRidingMount() && player->getParent() == pet) {

		if (!player->checkCooldownRecovery("mount_dismount"))
			return;

		player->executeObjectControllerAction(String("dismount").hashCode());

		if (player->isRidingMount())
			return;
	}

	pet->setPosture(CreaturePosture::UPRIGHT, false);
	pet->setTargetObject(NULL);
	pet->setFollowObject(NULL);
	pet->destroyObjectFromWorld(true);

	pet->setCreatureLink(NULL);

	updateStatus(0);
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
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject != NULL) {
		if (controlledObject->isInQuadTree())
			return 1;
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

void PetControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("creature_vitality", String::valueOf(vitality) + "/" + String::valueOf(maxVitality));
}
