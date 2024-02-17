/*
*	Copyright (C) 2007-2024 SWGEmu
*	See file COPYING for copying conditions.
*
*	Created By: Hakry
*	Date: 1/30/2024
*/

#include "server/zone/objects/tangible/misc/LightObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"

// #define DEBUG_LIGHTS

void LightObjectImplementation::initializeMembers() {
	lifespan.updateToCurrentTime();
	creationMili = System::getMiliTime();

	burntOut = false;
	firstUpdate = true;
}

void LightObjectImplementation::notifyInsertToZone(Zone* zone) {
	if (!burntOut && getObservers(ObserverEventType::PARENTCHANGED).size() == 0) {
		ManagedReference<LightObserver*> observer = new LightObserver();

		if (observer != nullptr) {
			registerObserver(ObserverEventType::PARENTCHANGED, observer);
		}
	}

	TangibleObjectImplementation::notifyInsertToZone(zone);
}

void LightObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	if (isClientObject())
		return;

	TangibleObjectImplementation::fillAttributeList(alm, player);

	Time now;
	int remainingSeconds = lifespan.getTime() - now.getTime();

	// Candle/Lamp is burnt out, no need to calculate any times
	if (burntOut || (!firstUpdate && remainingSeconds < 1)) {
		alm->insertAttribute("@obj_attr_n:lifespan", "0 days.");
		return;
	}

	// Light is not in a cell
	if (firstUpdate) {
		remainingSeconds = lifespanSeconds;
	}

	bool wholeDaysOnly = (remainingSeconds % 86400) == 0;

#ifdef DEBUG_LIGHTS
	info(true) << "Remaining Seconds: " << remainingSeconds << " wholeDaysOnly: " << (wholeDaysOnly ? "TRUE" : "FALSE");
#endif
	StringBuffer msg;

	if (wholeDaysOnly) { // Whole days only, light has never been dropped
		msg << (remainingSeconds / 86400) << " days.";
	} else {
		int days = remainingSeconds / 86400;
		remainingSeconds -= days * 86400;

		int hours = remainingSeconds / 3600;
		remainingSeconds -= hours * 3600;

		int minutes = remainingSeconds / 60;
		remainingSeconds -= minutes * 60;

		msg << days << " days, " << hours << " hours, " << minutes << " minutes, " << remainingSeconds << " seconds.";
	}

	alm->insertAttribute("@obj_attr_n:lifespan", msg.toString());
}

void LightObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	// Candles use lifespan and lamps/lights use quality
	if (values->hasExperimentalAttribute("lifespan")) {
		calculateLifespan(values->getCurrentValue("lifespan"));
	} else if (values->hasExperimentalAttribute("quality")) {
		calculateLifespan(values->getCurrentValue("quality"));
	}

	TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);
}

void LightObjectImplementation::calculateLifespan(int lifespanVar) {
	lifespanSeconds = lifespanVar * 86400; // Converting from number of days to seconds

#ifdef DEBUG_LIGHTS
	info(true) << "final lifespan in seconds = " << lifespanSeconds;
#endif

	burntOut = false;
}

void LightObjectImplementation::updateLifespan() {
#ifdef DEBUG_LIGHTS
	info(true) << "updateLifespan -- called";
#endif

	if (burntOut || isClientObject())
		return;

	auto parent = getParent().get();

	// Check the candle or lamp is placed in a cell
	if (parent == nullptr || !parent->isCellObject()) {
		// Light has been picked up from cell
		if (!firstUpdate) {
			// Resest first update, light is not in cell
			firstUpdate = true;

			Time now;

			// Save time remaining for lifespan in seconds
			lifespanSeconds = lifespan.getTime() - now.getTime();

#ifdef DEBUG_LIGHTS
			info(true) << " LIGHT HAS BEEN PICKED UP AND MODIFIED FOR STORAGE -- lifespanSeconds =  " << lifespanSeconds;
#endif
		}

		return;
	}

	if (!firstUpdate) {
		return;
	}

	firstUpdate = false;

	uint64 lifespanMili = ((uint64)lifespanSeconds) * 1000;

#ifdef DEBUG_LIGHTS
	info(true) << "Light firstUpdate -- lifespanMili: " << lifespanMili << " using lifespanSeconds: " << lifespanSeconds;
#endif

	// Update lifespan time
	lifespan.updateToCurrentTime();
	lifespan.addMiliTime(lifespanMili);
}

void LightObjectImplementation::updateTemplate() {
#ifdef DEBUG_LIGHTS
	info(true) << "updateTemplate - called";
#endif

	auto sharedTemp = getObjectTemplate();

	if (sharedTemp == nullptr)
		return;

	String templateName = sharedTemp->getClientTemplateFileName();

#ifdef DEBUG_LIGHTS
	info(true) << "updateTemplate -  Current Template Name: " << templateName;
#endif

	if (!templateName.contains("shared_frn_all_light_")) {
		// Lamp is an unlit type
		burntOut = true;
		return;
	}

	String newObjectTemplate = templateName.replaceFirst("shared_frn_all_light_", "frn_all_");

#ifdef DEBUG_LIGHTS
	info(true) << "New Object Template: " << newObjectTemplate;
#endif

	auto zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return;

	auto parent = getParent().get();

	if (parent == nullptr)
		return;

	ObjectManager* objectManager = ObjectManager::instance();

	uint32 newHash = newObjectTemplate.hashCode();

	ManagedReference<LightObject*> newLight = zoneServer->createObject(newHash, 1).castTo<LightObject*>();

	if (newLight == nullptr)
		return;

	Locker clock(newLight, asTangibleObject());

#ifdef DEBUG_LIGHTS
	info(true) << " New Light created: " << newLight->getDisplayedName();
#endif

	newLight->setBurntOut(true);

	// Update Crafters information
	newLight->setCraftersName(craftersName);
	newLight->setCraftersID(craftersID);
	newLight->setSerialNumber(objectSerial);

	newLight->setCustomObjectName(getCustomObjectName(), false);

	if (!parent->transferObject(newLight, -1, false, true)) {
		newLight->destroyObjectFromWorld(true);
		newLight->destroyObjectFromDatabase(true);

		return;
	}

	// Destroy this object
	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);

	parent->broadcastObject(newLight, true);
}

bool LightObjectImplementation::lifespanIsPast() {
	return lifespan.isPast();
}
