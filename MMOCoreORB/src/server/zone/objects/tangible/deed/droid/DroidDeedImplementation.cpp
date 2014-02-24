/*
 * DroidDeedImplementation.cpp
 *
 *  Created on: October 23, 2013
 *      Author: Klivian
 */

#include "server/zone/objects/tangible/deed/droid/DroidDeed.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/tangible/DroidDeedTemplate.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/customization/CustomizationIdManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"

void DroidDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	DroidDeedTemplate* deedData = dynamic_cast<DroidDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
	mobileTemplate = deedData->getMobileTemplate();
}

void DroidDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	// @TODO Add attributes

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

	// @TODO Add crafting values
}

void DroidDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if(isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_unpack"); //"Ready Droid Unit"
}

int DroidDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (selectedID == 20) {

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

		// Check if this will exceed maximum number of droids allowed
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int droidsInDatapad = 0;
		int maxStoredDroids = playerManager->getBaseStoredDroids();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != NULL && obj->isPetControlDevice() ){
				Reference<PetControlDevice*> petDevice = cast<PetControlDevice*>(obj.get());
				if( petDevice != NULL && petDevice->getPetType() == PetManager::DROIDPET){
					droidsInDatapad++;
				}
			}
		}

		if( droidsInDatapad >= maxStoredDroids){
			player->sendSystemMessage("You have too many droids in your datapad");
			return 1;
		}

		Reference<PetControlDevice*> controlDevice = (server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1)).castTo<PetControlDevice*>();
		if( controlDevice == NULL ){
			player->sendSystemMessage("wrong droid control device template " + controlDeviceObjectTemplate);
			return 1;
		}

		Reference<CreatureManager*> creatureManager = player->getZone()->getCreatureManager();
		if( creatureManager == NULL )
			return 1;

		Reference<CreatureObject*> creatureObject = creatureManager->createCreature(generatedObjectTemplate.hashCode(), true, mobileTemplate.hashCode() );
		if( creatureObject == NULL ){
			player->sendSystemMessage("wrong droid templates;mobileTemplate=[" + mobileTemplate + "];generatedObjectTemplate=[" + generatedObjectTemplate + "]" );
			return 1;
		}

		Reference<DroidObject*> droid = creatureObject.castTo<DroidObject*>();
		if( droid == NULL )
			return 1;

		CreatureTemplateManager* creatureTemplateManager = CreatureTemplateManager::instance();
		Reference<CreatureTemplate*> creatureTemplate =  creatureTemplateManager->getTemplate( mobileTemplate.hashCode() );
		if( creatureTemplate == NULL ){
			player->sendSystemMessage("wrong droid template;mobileTemplate=[" + mobileTemplate + "]" );
			return 1;
		}

		droid->loadTemplateData( creatureTemplate );

		// Transfer crafting components from deed to droid
		ManagedReference<SceneObject*> craftingComponents = getSlottedObject("crafted_components");
		if(craftingComponents != NULL) {
			droid->transferObject(craftingComponents, 4, false);
			craftingComponents->setSendToClient(false);
		}

		// Copy color customization from deed to droid
		CustomizationVariables* customVars = getCustomizationVariables();
		if( customVars != NULL ){
			for (int i = 0; i < customVars->size(); ++i) {
				uint8 id = customVars->elementAt(i).getKey();
				int16 val = customVars->elementAt(i).getValue();

				String name = CustomizationIdManager::instance()->getCustomizationVariable(id);
				if( name.contains( "color" ) ){
					droid->setCustomizationVariable( name, val, true );
				}
			}
			droid->refreshPaint();
		}

		StringId s;
		s.setStringId(droid->getObjectName()->getFullPath());
		controlDevice->setObjectName(s);
		controlDevice->setPetType(PetManager::DROIDPET);
		controlDevice->setMaxVitality(100);
		controlDevice->setVitality(100);
		controlDevice->setDefaultCommands();
		droid->createChildObjects();
		controlDevice->setControlledObject(droid);
		datapad->transferObject(controlDevice, -1);

		datapad->broadcastObject(controlDevice, true);
		controlDevice->callObject(player);

		//Remove the deed from its container.
		ManagedReference<SceneObject*> deedContainer = getParent();

		if (deedContainer != NULL) {
			destroyObjectFromWorld(true);
		}

		generated = true;
		player->sendSystemMessage("@pet/pet_menu:device_added"); // "A control device has been added to your datapad."
		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}

