/*
 * DroidDeedImplementation.cpp
 *
 *  Created on: October 23, 2013
 *      Author: Klivian
 */

#include "server/zone/objects/tangible/deed/droid/DroidDeed.h"
#include"server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/templates/tangible/DroidDeedTemplate.h"
#include "server/zone/objects/intangible/DroidControlDevice.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/tangible/deed/droid/DroidCraftingModule.h"
#include <iostream>

void DroidDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	DroidDeedTemplate* deedData = dynamic_cast<DroidDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
}

void DroidDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	// Add module attributes
	for( int i=0; i<modules.size(); i++){
		DroidModule* module = modules.get(i);

		if( module != NULL ){
			module->fillAttributeList(alm, object);
		}

	}

}

void DroidDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("DroidDeed");
}

void DroidDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 *
	 */

	std::string s(values->toString().toCharArray());
	std::cout << s << "\n";

	// Crafting Modules
	if( values->getCurrentValue("crafting_module") > 0 ){
		DroidCraftingModule* module = new DroidCraftingModule(values);
		modules.add(module);
	}

}

void DroidDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_unpack"); //"Ready Droid Unit"
}

int DroidDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	if (generated || !isASubChildOf(player))
		return 1;

	if (player->isInCombat() || player->isRidingMount() || player->isSwimming() || player->isDead() || player->isIncapacitated() ){
		player->sendSystemMessage("@pet/pet_menu:cant_call"); // "You cannot call this pet right now."
		return 1;
	}

	ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

	if (datapad == NULL) {
		player->sendSystemMessage("Datapad doesn't exist when trying to generate droid");
		return 1;
	}

	Reference<DroidControlDevice*> droidControlDevice = (server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1)).castTo<DroidControlDevice*>();
	if( droidControlDevice == NULL ){
		player->sendSystemMessage("wrong droid control device template " + controlDeviceObjectTemplate);
		return 1;
	}

	Reference<DroidObject*> droid = (server->getZoneServer()->createObject(generatedObjectTemplate.hashCode(), 1)).castTo<DroidObject*>();
	if (droid == NULL) {
		player->sendSystemMessage("wrong droid object template " + generatedObjectTemplate);
		return 1;
	}

	StringId s;
	s.setStringId(droid->getDisplayedName());
	droidControlDevice->setObjectName(s);

	droid->createChildObjects();
	droid->setMaxCondition(1000); // @TODO Set appropriate condition from deed
	droid->setConditionDamage(0);

	// Add modules
	for( int i=0; i<modules.size(); i++){
		droid->addModule( modules.get(i) );
	}

	droidControlDevice->setControlledObject(droid);
	datapad->transferObject(droidControlDevice, -1);

	datapad->broadcastObject(droidControlDevice, true);
	droidControlDevice->callObject(player);

	//Remove the deed from its container.
	ManagedReference<SceneObject*> deedContainer = getParent();

	if (deedContainer != NULL) {
		destroyObjectFromWorld(true);
	}

	generated = true;

	return 0;
}

