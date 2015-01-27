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
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/templates/tangible/DroidDeedTemplate.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/managers/customization/CustomizationIdManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/IngredientSlot.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/managers/crafting/labratories/DroidMechanics.h"

void DroidDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	DroidDeedTemplate* deedData = dynamic_cast<DroidDeedTemplate*>(templateData);

	if (deedData == NULL)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
	mobileTemplate = deedData->getMobileTemplate();
	species = deedData->getSpecies();
	overallQuality = 0;
}

void DroidDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	// @TODO Add attributes
	String key;
	ManagedReference<DroidComponent*> comp = NULL;
	HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();
	for(int i = 0; i < modules.size(); ++i) {
		iterator.getNextKeyAndValue(key, comp);
		if (comp) {
			DataObjectComponentReference* data = comp->getDataObjectComponent();
			BaseDroidModuleComponent* module = NULL;
			if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData() ){
				module = cast<BaseDroidModuleComponent*>(data->get());
			}
			if (module == NULL) {
				continue;
			}
			module->fillAttributeList(alm,object);
		}
	}
}

void DroidDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();
	overallQuality = 0;
	setLoggingName("DroidDeed");
}

void DroidDeedImplementation::processModule(BaseDroidModuleComponent* module, uint32 crc) {
	if (module == NULL)
		return;
	if (module->isStackable()) {
		if (modules.containsKey(module->getModuleName())) {
			// add to the stack if stackable.
			DroidComponent* comp = modules.get(module->getModuleName());
			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(comp->getDataObjectComponent()->get());
			bmodule->addToStack(module);
		} else {
			ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc,1)).castTo<DroidComponent*>();
			dcomp->setParent(NULL);
			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());
			bmodule->copy(module);
			bmodule->setSpecies(species);
			modules.put(module->getModuleName(),dcomp);
		}
	} else {
		ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc,1)).castTo<DroidComponent*>();
		dcomp->setParent(NULL);
		BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());
		bmodule->copy(module);
		bmodule->setSpecies(species);
		modules.put(module->getModuleName(),dcomp);
	}

}
void DroidDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 *
	 */
	String key;
	ManagedReference<DroidComponent*> comp = NULL;
	HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();
	for(int i = 0; i < modules.size(); ++i) {
		iterator.getNextKeyAndValue(key, comp);
		if (comp) {
			comp->destroyObjectFromWorld(true);
			comp->destroyObjectFromDatabase(true);
		}
	}
	modules.removeAll();
	overallQuality = values->getCurrentValue("exp_effectiveness");
	if (overallQuality < 0) {
		overallQuality = 1;
	}
	// @TODO Add crafting values, this should adjust toHit and Speed based on droid ham, also

	// we need to stack modules if they are stackable.
	// walk all components and ensure we have all modules that are stackable there.

	ManagedReference<ManufactureSchematic*> manufact = values->getManufactureSchematic();
	for (int i = 0; i < manufact->getSlotCount(); ++i) {
		// Droid Component Slots
		Reference<IngredientSlot* > iSlot = manufact->getSlot(i);
		if (iSlot->isComponentSlot()) {
			ComponentSlot* cSlot = cast<ComponentSlot*>(iSlot.get());
			ManagedReference<TangibleObject*> tano = cSlot->getPrototype();
			ManagedReference<DroidComponent*> component = cast<DroidComponent*>( tano.get());
			// only check modules
			if (component != NULL) {
				if (component->isSocketCluster()) {
					// pull out the objects
					ManagedReference<SceneObject*> craftingComponents = component->getSlottedObject("crafted_components");
					if(craftingComponents != NULL) {
						SceneObject* satchel = craftingComponents->getContainerObject(0);
						for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
							ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
							if (sceno != NULL) {
								// now we have the componet used in this socket item
								ManagedReference<DroidComponent*> sub = cast<DroidComponent*>( sceno.get());
								if (sub != NULL) {
									DataObjectComponentReference* data = sub->getDataObjectComponent();
									BaseDroidModuleComponent* module = NULL;
									if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData() ){
										module = cast<BaseDroidModuleComponent*>(data->get());
									}
									if (module == NULL) {
										continue;
									}
									processModule(module,sceno->getServerObjectCRC());
								}
							}
						}
					}
				} else {
					DataObjectComponentReference* data = component->getDataObjectComponent();
					BaseDroidModuleComponent* module = NULL;
					if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData() ){
						module = cast<BaseDroidModuleComponent*>(data->get());
					}
					if (module == NULL) {
						continue;
					}
					processModule(module,tano->getServerObjectCRC());
				}
			}
		}
	}
	// module stacking is completed! .. todo calc other stats
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

		Reference<CreatureManager*> creatureManager = player->getZone()->getCreatureManager();
		if( creatureManager == NULL )
			return 1;

		CreatureTemplateManager* creatureTemplateManager = CreatureTemplateManager::instance();
		Reference<CreatureTemplate*> creatureTemplate =  creatureTemplateManager->getTemplate( mobileTemplate.hashCode() );
		if( creatureTemplate == NULL ){
			player->sendSystemMessage("wrong droid template;mobileTemplate=[" + mobileTemplate + "]" );
			return 1;
		}

		Reference<PetControlDevice*> controlDevice = (server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1)).castTo<PetControlDevice*>();
		if( controlDevice == NULL ){
			player->sendSystemMessage("wrong droid control device template " + controlDeviceObjectTemplate);
			return 1;
		}

		Reference<CreatureObject*> creatureObject = creatureManager->createCreature(generatedObjectTemplate.hashCode(), true, mobileTemplate.hashCode() );
		if( creatureObject == NULL ){
			controlDevice->destroyObjectFromDatabase(true);
			player->sendSystemMessage("wrong droid templates;mobileTemplate=[" + mobileTemplate + "];generatedObjectTemplate=[" + generatedObjectTemplate + "]" );
			return 1;
		}

		Reference<DroidObject*> droid = creatureObject.castTo<DroidObject*>();
		if( droid == NULL ) {
			controlDevice->destroyObjectFromDatabase(true);
			creatureObject->destroyObjectFromDatabase(true);
			return 1;
		}

		droid->loadTemplateData( creatureTemplate );
		droid->setSpecies(species);
		droid->setCustomObjectName(StringIdManager::instance()->getStringId(*droid->getObjectName()), true);

		// Transfer crafting components from deed to droid
		ManagedReference<SceneObject*> craftingComponents = getSlottedObject("crafted_components");
		if(craftingComponents != NULL) {
			SceneObject* satchel = craftingComponents->getContainerObject(0);
			// remove all items form satchel and add int he new items
			Vector<ManagedReference<SceneObject*> > toRemove;
			for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
				ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
				if (sceno != NULL) {
					toRemove.add(sceno);
				}
			}
			satchel->removeAllContainerObjects();
			for(int i=0;i<toRemove.size();i++) {
				toRemove.get(i)->destroyObjectFromWorld(true);
			}
			// this will change to use stacked modules. we wont care about non droid modules as they arent needed.
			String key;
			ManagedReference<DroidComponent*> comp = NULL;
			HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();
			for(int i = 0; i < modules.size(); ++i) {
				iterator.getNextKeyAndValue(key, comp);
				if (comp) {
					satchel->transferObject(comp, -1, false);
					DataObjectComponentReference* data = comp->getDataObjectComponent();
					BaseDroidModuleComponent* module = NULL;
					if(data != NULL && data->get() != NULL && data->get()->isDroidModuleData()) {
						module = cast<BaseDroidModuleComponent*>(data->get());
						module->initialize(droid);
					}
				}
			}
			droid->transferObject(craftingComponents, 4, false);
			craftingComponents->setSendToClient(false);
		}
		if(droid->isCombatDroid()) {
			// change ham to match overall setup
			float maxHam = DroidMechanics::determineHam(overallQuality,species);
			for (int i = 0; i < 9; ++i) {
				if (i % 3 == 0) {
					droid->setMaxHAM(i,maxHam,true);
					droid->setHAM(i,maxHam,true);
				} else {
					droid->setMaxHAM(i,maxHam/100,true);
					droid->setHAM(i,maxHam/100,true);
				}
			}
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
		droid->createChildObjects();
		controlDevice->setControlledObject(droid);
		controlDevice->setDefaultCommands();

		if (!datapad->transferObject(controlDevice, -1)) {
			controlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

		datapad->broadcastObject(controlDevice, true);

		Locker crossLocker (droid, player);

		controlDevice->callObject(player);
		droid->initDroidModules();
		//Remove the deed from its container.
		ManagedReference<SceneObject*> deedContainer = getParent();

		if (deedContainer != NULL) {
			destroyObjectFromWorld(true);
		}
		generated = true;
		destroyObjectFromDatabase(true);

		player->sendSystemMessage("@pet/pet_menu:device_added"); // "A control device has been added to your datapad."
		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}
