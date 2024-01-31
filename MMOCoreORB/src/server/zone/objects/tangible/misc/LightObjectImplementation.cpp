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

void LightObjectImplementation::initializeMembers() {
	burntOut = false;
	firstUpdate = true;

	lifespan.updateToCurrentTime();
	creationMili = System::getMiliTime();

	setLoggingName("LightObject");
}

void LightObjectImplementation::notifyInsert(TreeEntry* object) {
	// Not a crafted candle or lamp
	if (getCraftersID() == 0)
		return;

	auto sceneO = static_cast<SceneObject*>(object);

	if (sceneO == nullptr || !sceneO->isPlayerCreature())
		return;

	Locker lock(_this.getReferenceUnsafeStaticCast());

	// Upate the light lifespan
	updateLifespan();
}

void LightObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	TangibleObjectImplementation::fillAttributeList(alm, player);

	// Candle/Lamp is burnt out, no need to calculate any times
	if (burntOut) {
		alm->insertAttribute("@obj_attr_n:lifespan", "0 days.");
		return;
	}

	// Upate the light lifespan
	updateLifespan();

	int remainingSeconds = (lifespanMili / 1000) % 86400;

	info(true) << "Remining Seconds after Days Modulo: " << remainingSeconds;

	StringBuffer msg;

	if (remainingSeconds == 0) { // Whole days only, light has never been dropped
		int days = lifespanMili / 1000 / 86400;
		msg << (int)days << " days.";

		info(true) << "Total Whole Days: " << days;
	} else {
		// Update lifespan time
		lifespan.updateToCurrentTime();
		lifespan.addMiliTime(lifespanMili);

		msg << lifespan.getFormattedTime("%d days, %H hours, %M minutes, %S seconds.");
	}

	alm->insertAttribute("@obj_attr_n:lifespan", msg.toString());
}

void LightObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	// Candles use lifespan and lamps/lights use quality
	if (values->hasExperimentalAttribute("lifespan")) {
		calculateLifespan(values->getCurrentValue("lifespan"));
	} else if (values->hasExperimentalAttribute("quality")) {
		calculateLifespan(values->getCurrentValue("quality"), true);
	}

	TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);
}

void LightObjectImplementation::calculateLifespan(float lifespanVar, bool lamp) {
	int minLife = LIFESPAN_CANDLE_MIN;
	int maxLife = LIFESPAN_CANDLE_MAX;

	if (lamp) {
		minLife = LIFESPAN_LAMP_MIN;
		maxLife = LIFESPAN_LAMP_MAX;
	}

	info(true) << "calculateLifespan - Lifespan variable: " << lifespanVar;

	int newLifespan = lifespanVar * 86400; // Converting lifespan in days to seconds

	info(true) << "calculated lifespan = " << newLifespan;

	// Check to ensure we havent gone over the max lifespan or under the min lifespan
	if (newLifespan > maxLife) {
		newLifespan = maxLife;
	} else if (newLifespan < minLife) {
		newLifespan = minLife;
	}

	info(true) << "final lifespan = " << newLifespan;

	lifespanMili = newLifespan * 1000;

	// Update lifespan time
	lifespan.updateToCurrentTime();
	lifespan.addMiliTime(lifespanMili);
}

void LightObjectImplementation::updateLifespan() {
	if (burntOut)
		return;

	auto parent = getParent().get();

	// Check the candle or lamp is placed in a cell
	if (parent == nullptr || !parent->isCellObject()) {
		// Resest first update, light is not in cell
		firstUpdate = true;
		return;
	}

	// Item has just been dropped again into a cell, reset the last decay time
	if (firstUpdate) {
		lastDecay.updateToCurrentTime();
		firstUpdate = false;
		return;
	}

	info(true) << "updateLifespan -- Remaining Lifespan Mili: " << lifespanMili;

	Time now;

	uint64 timeSinceDecay = lastDecay.miliDifference(now);

	if (timeSinceDecay > lifespanMili) {
		lifespanMili = 0;
	} else {
		lifespanMili -= timeSinceDecay;
	}

	info(true) << "New lifespanMili: " << lifespanMili << " timeSinceDecay: " << timeSinceDecay;

	// Update lifespan time
	lifespan.updateToCurrentTime();
	lifespan.addMiliTime(lifespanMili);

	// Update last decay time
	lastDecay.updateToCurrentTime();

	// Candle or lamp has decayed, change template to non lit version
	if (lifespanMili == 0)
		updateTemplate();
}

void LightObjectImplementation::updateTemplate() {
	auto sharedTemp = getObjectTemplate();

	if (sharedTemp == nullptr)
		return;

	String templateName = sharedTemp->getClientTemplateFileName();

	// info(true) << "updateTemplate -  Current Template Name: " << templateName;

	if (!templateName.contains("shared_frn_all_light_"))
		return;

	String newObjectTemplate = templateName.replaceFirst("shared_frn_all_light_", "frn_all_");

	// info(true) << "New Object Template: " << newObjectTemplate;

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

	// info(true) << " New Light created: " << newLight->getDisplayedName();

	newLight->initializePosition(getPositionX(), getPositionZ(), getPositionY());
	newLight->setDirection(*getDirection());

	// Update Crafters information
	newLight->setCraftersName(craftersName);
	newLight->setCraftersID(craftersID);
	newLight->setSerialNumber(objectSerial);

	newLight->setCustomObjectName(getCustomObjectName(), false);
	newLight->setBurntOut(true);

	if (!parent->transferObject(newLight, -1, true, true, true)) {
		newLight->destroyObjectFromWorld(true);
		newLight->destroyObjectFromDatabase(true);

		return;
	}

	// Destroy this object
	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);
}
