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
	lifespan = 0.f;
	creationMili = System::getMiliTime();

	setLoggingName("LightObject");
}

void LightObjectImplementation::notifyInsert(TreeEntry* object) {
	// Not a crafter candle or lamp
	if (getCraftersID() == 0 || lifespan == 0)
		return;

	auto sceneO = static_cast<SceneObject*>(object);

	if (sceneO == nullptr || !sceneO->isPlayerCreature())
		return;

	Locker lock(_this.getReferenceUnsafeStaticCast());

	// Upate the candle lifespan
	updateLifespan();
}

void LightObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	TangibleObjectImplementation::fillAttributeList(alm, player);

	int lifespanInt = (int)lifespan;

	StringBuffer msg;
	msg << (int)lifespan << " days.";

	alm->insertAttribute("@obj_attr_n:lifespan", msg.toString());
}

void LightObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	// Candles use lifespan and lamps/lights use quality
	if (values->hasExperimentalAttribute("lifespan")) {
		calculateLifespan(values->getCurrentValue("lifespan"));
	} else if (values->hasExperimentalAttribute("quality")) {
		calculateLifespan(values->getCurrentValue("quality"), true);
	}

	// info(true) << "LightObjectImplementation::updateCraftingValues = lifespan = " << lifespan;

	TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);
}

void LightObjectImplementation::calculateLifespan(float newLifespan, bool lamp) {
	int minLife = LIFESPAN_CANDLE_MIN;
	int maxLife = LIFESPAN_CANDLE_MAX;

	if (lamp) {
		minLife = LIFESPAN_LAMP_MIN;
		maxLife = LIFESPAN_LAMP_MAX;
	}

	int deltaLifespan = maxLife - minLife;

	newLifespan = ((newLifespan / 100.f) * deltaLifespan) + minLife;

	// TEST
	newLifespan = 0.0034;

	if (newLifespan > maxLife)
		newLifespan = maxLife;

	lifespan = newLifespan;
	decayedMili = System::getMiliTime() + lifespan * 24 * 60 * 60 * 1000;
}

void LightObjectImplementation::updateLifespan() {
	auto parent = getParent().get();

	// Check the candle or lamp is placed in a cell
	if (parent == nullptr || !parent->isCellObject())
		return;

	float currentLife = getLifespan();

	// Already decayed, no need to update
	if (currentLife <= 0)
		return;

	uint64 miliTime = System::getMiliTime();

	// info(true) << "updateLifespan - Mili Time Now: " << miliTime << " End of life Decayed Mili: " << decayedMili;

	if (miliTime >= decayedMili) {
		lifespan = 0;
	} else {
		// End of life mili time with current mili time subtracted, leaving time remaining
		uint64 miliReminaing = decayedMili - miliTime;

		lifespan = miliReminaing / 1000 / 60 / 60 / 24.f;

		// info(true) << "Lifespan updated - miliRemaining: " << miliReminaing << " New Lifespan: " << lifespan;
	}

	// info(true) << "updateLifespan - New Lifespan: " << lifespan;

	// Candle or lamp has decay, change template to non lit version
	if (lifespan == 0)
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

	ManagedReference<LightObject*> newLight = zoneServer->createObject(newHash, 1).castTo<LightObject*>(); //objectManager->cloneObject(asTangibleObject(), false, newHash));

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

	if (!parent->transferObject(newLight, -1, true, true, true)) {
		newLight->destroyObjectFromWorld(true);
		newLight->destroyObjectFromDatabase(true);

		return;
	}

	// Destroy this object
	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);
}
