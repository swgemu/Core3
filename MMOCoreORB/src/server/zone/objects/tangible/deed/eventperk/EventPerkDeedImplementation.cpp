
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/tangible/tasks/RemoveEventPerkTask.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/templates/tangible/EventPerkDeedTemplate.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/structure/StructureManager.h"

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

	Time currentTime;
	uint32 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();
	String timeLeft = getDurationString((TIME_TO_LIVE - timeDelta) / 1000);
	alm->insertAttribute("duration", timeLeft); // Duration
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

		if (zone->getZoneName().contains("space_")) {
			player->sendSystemMessage("@event_perk:not_in_space"); // You may not deploy a Rental in space. Return to the ground first.
			return 1;
		}

		if (!isASubChildOf(player)) {
			player->sendSystemMessage("@event_perk:from_inventory_only"); // This rental must be in your inventory in order to be deployed.
			return 1;
		}

		if (player->getParent() != NULL) {
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

		ManagedReference<TangibleObject*> object = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), 1)).castTo<TangibleObject*>();

		if (object == NULL) {
			player->sendSystemMessage("Error generating object. Wrong generatedObjectTemplate or is not a tangible object.");
			return 1;
		}

		generatedObject = object;

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
		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != NULL) {
			ghost->removeEventPerk();
		}
	}

	DeedImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void EventPerkDeedImplementation::activateRemoveEvent() {
	if (removeEventPerkTask == NULL) {
		removeEventPerkTask = new RemoveEventPerkTask(_this.get());

		Time currentTime;
		uint32 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

		if (timeDelta >= TIME_TO_LIVE) {
			removeEventPerkTask->execute();
		} else {
			removeEventPerkTask->schedule(TIME_TO_LIVE - timeDelta);
		}
	}
}

String EventPerkDeedImplementation::getDurationString(uint32 timestamp) {

	if( timestamp == 0 ){
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
