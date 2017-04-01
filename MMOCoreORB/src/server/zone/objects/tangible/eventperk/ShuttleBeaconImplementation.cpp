#include "server/zone/objects/tangible/eventperk/ShuttleBeacon.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkItemTask.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/player/sui/callbacks/ShuttleBeaconSuiCallback.h"

void ShuttleBeaconImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	activateRemoveEvent();
}

void ShuttleBeaconImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("duration", getDurationString()); // Duration
}

void ShuttleBeaconImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ManagedReference<CreatureObject*> perkOwner = owner.get();
	ManagedReference<SceneObject*> beaconParent = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (perkOwner == NULL || beaconParent == NULL || perkOwner != beaconParent)
		return;

	if (shuttleStatus == 0)
		menuResponse->addRadialMenuItem(20, 3, "@event_perk:call_shuttle"); // Contact Shuttle
	else
		menuResponse->addRadialMenuItem(20, 3, "@event_perk:dismiss_shuttle"); // Dismiss Shuttle
}

int ShuttleBeaconImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	ManagedReference<CreatureObject*> perkOwner = owner.get();
	ManagedReference<SceneObject*> beaconParent = getParentRecursively(SceneObjectType::PLAYERCREATURE);

	if (perkOwner == NULL || beaconParent == NULL || perkOwner != beaconParent || selectedID != 20)
		return 0;

	if (shuttleStatus == 0) {
		ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

		if (strongShuttle != NULL && strongShuttle->getZone() != NULL) {
			player->sendSystemMessage("@event_perk:already_have_shuttle"); // You already have a shuttle deployed.
			return 0;
		}

		callShuttle(player);
	} else if (shuttleStatus == 1) {
		if (!readyToTakeOff) {
			player->sendSystemMessage("@event_perk:shuttle_not_take_off"); // The shuttle is not yet ready for take off.
			return 0;
		}

		ManagedReference<ShuttleBeacon*> tempBeacon = _this.getReferenceUnsafeStaticCast();
		Reference<CreatureObject*> creo = player;
		Core::getTaskManager()->scheduleTask([tempBeacon, creo]{
			if(tempBeacon != NULL) {
				Locker locker(tempBeacon);
				tempBeacon->dismissShuttle(creo);
			}
		}, "DismissShuttleTask", 250);
	}

	return 0;
}

void ShuttleBeaconImplementation::callShuttle(CreatureObject* player) {
	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

	if (shuttleStatus == 1 && strongShuttle != NULL && strongShuttle->getZone() != NULL)
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::SHUTTLE_BEACON))
		ghost->closeSuiWindowType(SuiWindowType::SHUTTLE_BEACON);

	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::SHUTTLE_BEACON);
    listbox->setCallback(new ShuttleBeaconSuiCallback(getZoneServer()));
	listbox->setPromptTitle("@event_perk:shuttle_beacon_t"); // Select Shuttle Landing Type
	listbox->setPromptText("@event_perk:shuttle_beacon_d"); // Select the type of shuttle landing you would like to call. Contacting the shuttle again after it lands will order the shuttle to leave.
	listbox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	listbox->setForceCloseDistance(32.f);
	listbox->setCancelButton(true, "@cancel");

	listbox->addMenuItem("@event_perk:shuttle_lambda_shuttle");
	listbox->addMenuItem("@event_perk:shuttle_shuttle");
	listbox->addMenuItem("@event_perk:shuttle_transport_drop_down");
	listbox->addMenuItem("@event_perk:shuttle_transport_fly_in");

	ghost->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}

void ShuttleBeaconImplementation::spawnShuttle(CreatureObject* player, int type) {
	ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

	if (player == NULL || (strongShuttle != NULL && strongShuttle->getZone() != NULL))
		return;

	ManagedReference<ZoneServer*> zoneServer = getZoneServer();

	if (zoneServer == NULL)
		return;

	if (!canSpawnShuttle(player)) {
		player->sendSystemMessage("@event_perk:shuttle_not_called"); // A shuttle could not be called.
		return;
	}

	uint32 shuttleTemplate;

	switch (type) {
	case 3: shuttleTemplate = 0xB120E676; break; // object/creature/npc/theme_park/event_transport_theed_hangar.iff
	case 2: shuttleTemplate = 0xD3D6FBA1; break; // object/creature/npc/theme_park/event_transport.iff
	case 1: shuttleTemplate = 0x62A585E7; break; // object/creature/npc/theme_park/player_shuttle.iff
	case 0: shuttleTemplate = 0xCB59CE5C; break; // object/creature/npc/theme_park/lambda_shuttle.iff
	default: return;
	}

	shuttleType = type;

	ManagedReference<SceneObject*> object = zoneServer->createObject(shuttleTemplate, 0);

	if (object == NULL)
		return;

	CreatureObject* newShuttle = cast<CreatureObject*>( object.get());

	if (newShuttle == NULL)
		return;

	Locker locker(newShuttle);

	float direction = player->getDirectionAngle();

	if (shuttleType < 3)
		direction += 180;

	newShuttle->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
	newShuttle->setDirection(Math::deg2rad(direction));

	Zone* zn = player->getZone();

	zn->transferObject(newShuttle, -1, true);

	if (type == 1)
		newShuttle->setPosture(CreaturePosture::PRONE, true, true);

	shuttle = newShuttle;

	ManagedReference<ShuttleBeacon*> tempBeacon = _this.getReferenceUnsafeStaticCast();

	if (tempBeacon == NULL)
		return;

	Reference<CreatureObject*> creo = player;
	Core::getTaskManager()->scheduleTask([tempBeacon, creo] {
		Locker locker(tempBeacon);
		tempBeacon->landShuttle(creo);
	}, "LandShuttleTask", 250);
}

void ShuttleBeaconImplementation::landShuttle(CreatureObject* player) {
	ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

	if (strongShuttle == NULL)
		return;

	ManagedReference<ShuttleBeacon*> tempBeacon = _this.getReferenceUnsafeStaticCast();

	if (tempBeacon == NULL)
		return;

	Locker clocker(strongShuttle, _this.getReferenceUnsafeStaticCast());

	readyToTakeOff = false;

	if (shuttleType == 0 || shuttleType == 2) {
		strongShuttle->setPosture(CreaturePosture::PRONE, true, true);
	} else if (shuttleType == 1) {
		strongShuttle->setPosture(CreaturePosture::UPRIGHT, true, true);
	} else if (shuttleType == 3) {
		strongShuttle->setPosture(CreaturePosture::CROUCHED, true, true);
	} else {
		return;
	}

	player->sendSystemMessage("@event_perk:shuttle_is_landing"); // Transmission Recieved: Shuttle is inbound to destination.

	shuttleStatus = 1;


	Core::getTaskManager()->scheduleTask([tempBeacon] {
		Locker locker(tempBeacon);
		tempBeacon->setReadyToTakeOff(true);
	}, "ShuttleTakeOffTask", 40000);
}

void ShuttleBeaconImplementation::dismissShuttle(CreatureObject* player) {
	ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

	if (strongShuttle == NULL || player == NULL)
		return;

	ManagedReference<ShuttleBeacon*> tempBeacon = _this.getReferenceUnsafeStaticCast();

	if (tempBeacon == NULL)
		return;

	if (!readyToTakeOff) {
		player->sendSystemMessage("@event_perk:shuttle_not_take_off"); // The shuttle is not yet ready for take off.
		return;
	}

	Locker clocker(strongShuttle, _this.getReferenceUnsafeStaticCast());

	if (shuttleType == 1) {
		strongShuttle->setPosture(CreaturePosture::PRONE, true, true);
	} else {
		strongShuttle->setPosture(CreaturePosture::UPRIGHT, true, true);
	}

	shuttleStatus = 0;
	player->sendSystemMessage("@event_perk:shuttle_is_leaving"); // Transmission Recieved: Shuttle is leaving the area.


	Reference<CreatureObject*> creo = player;
	Core::getTaskManager()->scheduleTask([tempBeacon, creo] {
		Locker locker(tempBeacon);
		tempBeacon->destroyShuttle(creo);
	}, "DestroyShuttleTask", 20000);
}

void ShuttleBeaconImplementation::destroyShuttle(CreatureObject* player) {
	ManagedReference<CreatureObject*> strongShuttle = shuttle.get();

	if (strongShuttle == NULL)
		return;

	Locker locker(strongShuttle, _this.getReferenceUnsafeStaticCast());

	strongShuttle->destroyObjectFromWorld(true);

	if (player != NULL)
		player->sendSystemMessage("@event_perk:shuttle_next_is_ready"); // Shuttle Beacon: You may now call another shuttle.
}

bool ShuttleBeaconImplementation::canSpawnShuttle(CreatureObject* player) {
	Zone* zone = player->getZone();

	if (zone == NULL)
		return false;

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == NULL)
		return false;

	if (zone->getZoneName().contains("space_"))
		return false;

	if (!isASubChildOf(player))
		return false;

	ManagedReference<SceneObject*> parent = player->getParent().get();

	if (parent != NULL && parent->isCellObject())
		return false;

	if (player->isInCombat())
		return false;

	if (player->isSwimming())
		return false;

	ManagedReference<CityRegion*> city = player->getCityRegion().get();

	if (city != NULL) {
		if (city->isClientRegion())
			return false;

		if (city->isZoningEnabled() && !city->hasZoningRights(player->getObjectID()))
			return false;
	}

	int x = player->getWorldPositionX();
	int y = player->getWorldPositionY();
	int nearbyPerks = 0;

	CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();

	if (vec == NULL)
		return false;

	SortedVector<QuadTreeEntry*> closeObjects;
	vec->safeCopyTo(closeObjects);

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* obj = cast<SceneObject*>(closeObjects.get(i));

		if (obj == NULL)
			continue;

		SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

		if (objectTemplate == NULL)
			continue;

		float radius = objectTemplate->getNoBuildRadius();

		if (radius > 0 && player->isInRange(obj, radius))
			return false;

		if (objectTemplate->isSharedStructureObjectTemplate()) {
			if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), x, y, 0))
				return false;
		}

		if (obj->isEventPerk() && player->isInRange(obj, 32) && ++nearbyPerks > 2)
			return false;
	}

	SortedVector<ManagedReference<ActiveArea* > > activeAreas;
	zone->getInRangeActiveAreas(x, y, &activeAreas, true);

	for (int i = 0; i < activeAreas.size(); ++i) {
		ActiveArea* area = activeAreas.get(i);

		if (area->isNoBuildArea())
			return false;
	}

	if (planetManager->isInRangeWithPoi(x, y, 100))
		return false;

	return true;
}

void ShuttleBeaconImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	destroyShuttle(NULL);

	ManagedReference<CreatureObject*> strongOwner = owner.get();

	if (strongOwner != NULL) {
		Locker clocker(strongOwner, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != NULL) {
			ghost->removeEventPerk(_this.getReferenceUnsafeStaticCast());
		}
	}

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void ShuttleBeaconImplementation::activateRemoveEvent(bool immediate) {
	if (removeEventPerkItemTask == NULL) {
		removeEventPerkItemTask = new RemoveEventPerkItemTask(_this.getReferenceUnsafeStaticCast());

		Time currentTime;
		uint64 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

		if (timeDelta >= EventPerkDeedTemplate::TIME_TO_LIVE || immediate) {
			removeEventPerkItemTask->execute();
		} else {
			removeEventPerkItemTask->schedule(EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta);
		}
	} else if (immediate) {
		if (removeEventPerkItemTask->isScheduled()) {
			removeEventPerkItemTask->reschedule(1);
		} else {
			removeEventPerkItemTask->execute();
		}
	}
}

String ShuttleBeaconImplementation::getDurationString() {

	Time currentTime;
	uint32 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();
	uint32 timestamp = (EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta) / 1000;

	if( timestamp == 0 ) {
		return "";
	}

	String abbrvs[3] = { "seconds", "minutes", "hours" };

	int intervals[3] = { 1, 60, 3600 };
	int values[3] = { 0, 0, 0 };

	StringBuffer str;

	for (int i = 2; i > -1; --i) {
		values[i] = floor((float) timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0){
				str << ", ";
			}

			str << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}
