
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkDeedTask.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/terrain/TerrainManager.h"

void EventPerkDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	activateRemoveEvent();
}

void EventPerkDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);
	EventPerkDeedTemplate* deedData = dynamic_cast<EventPerkDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	perkType = deedData->getPerkType();
}

void EventPerkDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("duration", getDurationString()); // Duration
}

void EventPerkDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player)) {
		menuResponse->addRadialMenuItem(20, 3, "@event_perk:use_event_perk"); // Deploy Rental
	}
}

int EventPerkDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 20) {
		if (generated) {
			return 1;
		}

		Zone* zone = player->getZone();

		if (zone == NULL) {
			return 1;
		}

		PlanetManager* planetManager = zone->getPlanetManager();
		if (planetManager == NULL) {
			return 1;
		}

		EventPerkDeedTemplate* deedTemplate = cast<EventPerkDeedTemplate*>(getObjectTemplate());
		if (deedTemplate == NULL) {
			return 1;
		}

		if (zone->getZoneName().contains("space_")) {
			player->sendSystemMessage("@event_perk:not_in_space"); // You may not deploy a Rental in space. Return to the ground first.
			return 1;
		}

		if (!deedTemplate->isAllowedZone(zone->getZoneName())) {
			player->sendSystemMessage("@event_perk:not_on_this_planet"); // You cannot deploy this rental on this planet. Examine the deed to determine the intended planet for this rental.
			return 1;
		}

		if (!isASubChildOf(player)) {
			player->sendSystemMessage("@event_perk:from_inventory_only"); // This rental must be in your inventory in order to be deployed.
			return 1;
		}

		ManagedReference<SceneObject*> parent = player->getParent().get();

		if (parent != NULL && parent->isCellObject()) {
			player->sendSystemMessage("@event_perk:not_inside"); // You cannot deploy a Rental indoors. You must move outside.
			return 1;
		}

		if (player->isInCombat()) {
			player->sendSystemMessage("@event_perk:not_in_combat"); // You cannot deploy a Rental while in combat.
			return 1;
		}

		if (player->isSwimming()) {
			player->sendSystemMessage("@event_perk:not_while_swimming"); // You cannot deploy a Rental while swimming.
			return 1;
		}

		ManagedReference<CityRegion*> city = player->getCityRegion().get();

		if (city != NULL) {
			if (city->isClientRegion()) {
				player->sendSystemMessage("@event_perk:not_in_municipal_zone"); // You may not place a Rental in a municipal zone.
				return 1;
			}

			if (city->isZoningEnabled() && !city->hasZoningRights(player->getObjectID())) {
				player->sendSystemMessage("@event_perk:no_zoning_rights"); // You must have zoning rights to place a Rental in this city.
				return 1;
			}
		}

		int x = player->getWorldPositionX();
		int y = player->getWorldPositionY();
		int nearbyPerks = 0;

		TerrainManager* terrainManager = planetManager->getTerrainManager();
		if ( terrainManager == NULL || terrainManager->getHighestHeightDifference(x - 10, y - 10, x + 10, y + 10) > 15.0) {
			player->sendSystemMessage("@event_perk:bad_area"); // This rental could not be deployed due to the surrounding terrain. Please move to another area and try again.
			return 1;
		}

		CloseObjectsVector* vec = (CloseObjectsVector*) player->getCloseObjects();

		if (vec == NULL) {
			error("Player has NULL closeObjectsVector in EventPerkDeedImplementation::handleObjectMenuSelect");
			return 1;
		}

		SortedVector<ManagedReference<QuadTreeEntry* > > closeObjects;
		vec->safeCopyTo(closeObjects);

		for (int i = 0; i < closeObjects.size(); ++i) {
			SceneObject* obj = cast<SceneObject*>(closeObjects.get(i).get());

			if (obj == NULL) {
				continue;
			}

			SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();
			if (objectTemplate == NULL) {
				continue;
			}

			float radius = objectTemplate->getNoBuildRadius();

			if (obj->isLairObject() && player->isInRange(obj, radius)) {
				player->sendSystemMessage("@event_perk:too_close_lair"); // You cannot place a Rental this close to a lair.
				return 1;
			}

			if (obj->isCampStructure() && player->isInRange(obj, radius)) {
				player->sendSystemMessage("@event_perk:too_close_camp"); // You cannot place a Rental this close to a camp.
				return 1;
			}

			if (radius > 0 && player->isInRange(obj, radius)) {
				player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
				return 1;
			}

			if (objectTemplate->isSharedStructureObjectTemplate()) {
				if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), x, y, 0)) {
					player->sendSystemMessage("@event_perk:too_close_building"); // You may not place a Rental this close to a building.
					return 1;
				}
			}

			if (obj->isEventPerk() && player->isInRange(obj, 32) && ++nearbyPerks > 2) {
				player->sendSystemMessage("@event_perk:too_many_perks"); // There are too many Rentals already deployed in this area. Please move to another location.
				return 1;
			}
		}

		SortedVector<ManagedReference<ActiveArea* > > activeAreas;
		zone->getInRangeActiveAreas(x, y, &activeAreas, true);

		for (int i = 0; i < activeAreas.size(); ++i) {
			ActiveArea* area = activeAreas.get(i);

			if (area->isNoBuildArea()) {
				player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
				return 1;
			}
		}

		if (planetManager->isInRangeWithPoi(x, y, 150)) {
			player->sendSystemMessage("@event_perk:too_close_something"); // You are too close to an object to deploy your Rental here. Move away from it.
			return 1;
		}

		if (perkType != EventPerkDeedTemplate::STATIC && perkType != EventPerkDeedTemplate::GAME) {
			player->sendSystemMessage("This type of event perk deed is not functional yet.");
			return 1;
		}

		ManagedReference<TangibleObject*> object = generatedObject.get();

		if (object == NULL) {
			object = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), "playerstructures", 1)).castTo<TangibleObject*>();

			if (object == NULL) {
				player->sendSystemMessage("Error generating object. Wrong generatedObjectTemplate or is not a tangible object.");
				return 1;
			}

			generatedObject = object;
		}

		Locker locker(object);

		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(object->getDataObjectComponent()->get());

		if (data == NULL) {
			player->sendSystemMessage("Error: no dataObjectComponent.");
			object->destroyObjectFromDatabase(true);
			return 1;
		}

		data->setDeed(_this.getReferenceUnsafeStaticCast());

		object->initializePosition(player->getPositionX(), player->getPositionZ(), player->getPositionY());
		object->setDirection(Math::deg2rad(player->getDirectionAngle()));
		zone->transferObject(object, -1, true);

		generated = true;
		destroyObjectFromWorld(true);

		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

void EventPerkDeedImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<CreatureObject*> strongOwner = owner.get();

	if (strongOwner != NULL) {
		Locker clocker(strongOwner, _this.getReferenceUnsafeStaticCast());

		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != NULL) {
			ghost->removeEventPerk(_this.getReferenceUnsafeStaticCast());
		}
	}

	DeedImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void EventPerkDeedImplementation::activateRemoveEvent(bool immediate) {
	if (removeEventPerkDeedTask == NULL) {
		removeEventPerkDeedTask = new RemoveEventPerkDeedTask(_this.getReferenceUnsafeStaticCast());

		Time currentTime;
		uint64 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

		if (timeDelta >= EventPerkDeedTemplate::TIME_TO_LIVE || immediate) {
			removeEventPerkDeedTask->execute();
		} else {
			removeEventPerkDeedTask->schedule(EventPerkDeedTemplate::TIME_TO_LIVE - timeDelta);
		}
	} else if (immediate) {
		if (removeEventPerkDeedTask->isScheduled()) {
			removeEventPerkDeedTask->reschedule(1);
		} else {
			removeEventPerkDeedTask->execute();
		}
	}
}

String EventPerkDeedImplementation::getDurationString() {

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
