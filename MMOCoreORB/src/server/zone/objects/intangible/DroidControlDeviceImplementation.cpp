#include "server/zone/objects/intangible/DroidControlDevice.h"
#include "server/zone/objects/intangible/DroidControlObserver.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "tasks/CallDroidTask.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/creature/events/DroidPowerTask.h"


void DroidControlDeviceImplementation::callObject(CreatureObject* player) {

	if (player->getParent() != NULL){
		player->sendSystemMessage( "You must be outside to call this droid" );
		return;
	}

	if (!isASubChildOf(player)){
		return;
	}

	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();
	if (controlledObject == NULL){
		return;
	}

	if (controlledObject->isInQuadTree()){
		return;
	}

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

	if (!controlledObject->isAiAgent()){
		return;
	}

	ManagedReference<AiAgent*> droid = cast<AiAgent*>(controlledObject.get());

	if(player->getPendingTask("call_droid") != NULL) {
		StringIdChatParameter waitTime("pet/pet_menu", "call_delay_finish_pet"); // Already calling a Pet: Call will be finished in %DI seconds.
		Time nextExecution;
		Core::getTaskManager()->getNextExecutionTime(player->getPendingTask("call_droid"), nextExecution);
		int timeLeft = (nextExecution.getMiliTime() / 1000) - System::getTime();
		waitTime.setDI(timeLeft);

		player->sendSystemMessage(waitTime);
		return;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL){
		return;
	}

	int currentlySpawned = 0;

	int maxDroids = 1;

	for (int i = 0; i < datapad->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object = datapad->getContainerObject(i);

		if (object->isDroidControlDevice()) {
			DroidControlDevice* device = cast<DroidControlDevice*>( object.get());

			ManagedReference<AiAgent*> object = cast<AiAgent*>(device->getControlledObject());

			if (object != NULL && object->isInQuadTree()) {
				if ( object->isDroidObject()) {
					if (++currentlySpawned >= maxDroids) {
						player->sendSystemMessage("@pet/pet_menu:at_max"); // You already have the maximum number of pets of this type that you can call.
						return;
					}
				}

			}
		}
	}

	if(player->getCurrentCamp() == NULL && player->getCityRegion() == NULL) {

		Reference<CallDroidTask*> callDroid = new CallDroidTask(_this.get(), player, "call_droid");

		StringIdChatParameter message("pet/pet_menu", "call_pet_delay"); // Calling pet in %DI seconds. Combat will terminate pet call.
		message.setDI(15);
		player->sendSystemMessage(message);

		player->addPendingTask("call_droid", callDroid, 15 * 1000);

		if (droidControlObserver == NULL) {
			droidControlObserver = new DroidControlObserver(_this.get());
			droidControlObserver->deploy();
		}

		player->registerObserver(ObserverEventType::STARTCOMBAT, droidControlObserver);

	} else {

		Locker clocker(controlledObject, player);
		spawnObject(player);
	}

}

void DroidControlDeviceImplementation::spawnObject(CreatureObject* player) {
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
		// TODO: need to have the pet take on the faction status of the owner (Special Forces, Combatant, or On Leave)
	}

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	zone->transferObject(controlledObject, -1, true);

	updateStatus(1);

	if (droidControlObserver != NULL)
		player->dropObserver(ObserverEventType::STARTCOMBAT, droidControlObserver);

	DroidObject* droid = cast<DroidObject*>(creature.get());

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
		droid->setOblivious();
		droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
	}

}

void DroidControlDeviceImplementation::cancelSpawnObject(CreatureObject* player) {

	Reference<Task*> droidTask = player->getPendingTask("call_droid");
	if(droidTask) {
		droidTask->cancel();
		player->removePendingTask("call_droid");
	}

	if (droidControlObserver != NULL)
		player->dropObserver(ObserverEventType::STARTCOMBAT, droidControlObserver);
}

void DroidControlDeviceImplementation::storeObject(CreatureObject* player) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject == NULL || !controlledObject->isCreatureObject())
		return;

	ManagedReference<CreatureObject*> droid = cast<CreatureObject*>(controlledObject.get());

	if (droid->isInCombat())
		return;

	droid->removePendingTask( "droid_power" );

	droid->destroyObjectFromWorld(true);

	droid->setCreatureLink(NULL);

	updateStatus(0);
}


void DroidControlDeviceImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject != NULL) {
		Locker locker(controlledObject);
		controlledObject->destroyObjectFromDatabase(true);
	}

	IntangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

int DroidControlDeviceImplementation::canBeDestroyed(CreatureObject* player) {
	ManagedReference<TangibleObject*> controlledObject = this->controlledObject.get();

	if (controlledObject != NULL) {
		if (controlledObject->isInQuadTree())
			return 1;
	}

	return IntangibleObjectImplementation::canBeDestroyed(player);
}

void DroidControlDeviceImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	// TODO Add attributes
}
