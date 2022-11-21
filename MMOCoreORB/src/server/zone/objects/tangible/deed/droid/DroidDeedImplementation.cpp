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
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "templates/tangible/DroidDeedTemplate.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "templates/customization/CustomizationIdManager.h"
#include "server/zone/objects/scene/variables/CustomizationVariables.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/IngredientSlot.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/managers/crafting/labratories/DroidMechanics.h"

void DroidDeedImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	DeedImplementation::loadTemplateData(templateData);

	DroidDeedTemplate* deedData = dynamic_cast<DroidDeedTemplate*>(templateData);

	if (deedData == nullptr)
		return;

	controlDeviceObjectTemplate = deedData->getControlDeviceObjectTemplate();
	mobileTemplate = deedData->getMobileTemplate();
	species = deedData->getSpecies();
}

void DroidDeedImplementation::onCloneObject(SceneObject* objectToClone) {
	DeedImplementation::onCloneObject(objectToClone);

	ManagedReference<DroidDeed*> deed = cast<DroidDeed*>(objectToClone);
	if (deed == nullptr) {
		error("Invalid object type used in DroidDeedImplementation::onCloneObject");
		return;
	}

	//clear old modules
	modules.removeAll();

	// Insert our stacked droid modules into the droid's crafted components container
	String key;
	ManagedReference<DroidComponent*> comp = nullptr;

	auto modulesTable = deed->getModules();

	if (modulesTable != nullptr) {
		HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modulesTable->iterator();

		while (iterator.hasNext()) {
			iterator.getNextKeyAndValue(key, comp);

			if (comp != nullptr) {
				ManagedReference<DroidComponent*> cloneComponent = cast<DroidComponent*>(ObjectManager::instance()->cloneObject(comp));
				cloneComponent->setParent(nullptr);
				modules.put(key, cloneComponent);
			}
		}
	}
}

void DroidDeedImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	DeedImplementation::fillAttributeList(alm, object);

	// Use species to set challenge_level
	if (species == DroidObject::PROBOT) {
		level = 19;
	} else if (species == DroidObject::LE_REPAIR || species == DroidObject::DZ70 || (species == DroidObject::R_SERIES && combatRating > 0)) {
		level = 18;
	} else if (species == DroidObject::R_SERIES) {
		level = 7;
	} else {
		level = 1;
	}

	alm->insertAttribute("challenge_level", level);

	// HAM
	int maxHam = DroidMechanics::determineHam(overallQuality,species);
	alm->insertAttribute("creature_health", maxHam);
	alm->insertAttribute("creature_action", maxHam);
	alm->insertAttribute("creature_mind", maxHam);

    // Check for combat rating and apply attack, to-hit, and damage range attributes
	if (combatRating > 0) {
		float attackSpeed = DroidMechanics::determineSpeed(species,maxHam);
		float chanceHit = DroidMechanics::determineHit(species,maxHam);
		float damageMin = DroidMechanics::determineMinDamage(species,combatRating);
		float damageMax = DroidMechanics::determineMaxDamage(species,combatRating);

		StringBuffer attdisplayValue;
		StringBuffer hitdisplayValue;

		attdisplayValue << Math::getPrecision(attackSpeed, 2);
		hitdisplayValue << Math::getPrecision(chanceHit, 2);

		alm->insertAttribute("creature_attack", attdisplayValue);
		alm->insertAttribute("creature_tohit", hitdisplayValue);
		alm->insertAttribute("creature_damage", String::valueOf(damageMin) + " - " + String::valueOf(damageMax));
	}

	String key;
	ManagedReference<DroidComponent*> comp = nullptr;
	HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();

	for(int i = 0; i < modules.size(); ++i) {
		iterator.getNextKeyAndValue(key, comp);

		if (comp) {
			DataObjectComponentReference* data = comp->getDataObjectComponent();
			BaseDroidModuleComponent* module = nullptr;

			if(data != nullptr && data->get() != nullptr && data->get()->isDroidModuleData() ){
				module = cast<BaseDroidModuleComponent*>(data->get());
			}

			if (module == nullptr) {
				continue;
			}

			module->fillAttributeList(alm,object);
		}
	}
}

void DroidDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();
	setLoggingName("DroidDeed");
}

void DroidDeedImplementation::processModule(BaseDroidModuleComponent* module, uint32 crc) {
	if (module == nullptr)
		return;

	if (module->isStackable()) {
		if (modules.containsKey(module->getModuleName())) {
			// add to the stack if stackable.
			DroidComponent* comp = modules.get(module->getModuleName());
			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(comp->getDataObjectComponent()->get());

			if (bmodule != nullptr)
				bmodule->addToStack(module);
		} else {
			ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc, 1)).castTo<DroidComponent*>();
			dcomp->setParent(nullptr);

			BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());

			if (bmodule != nullptr) {
				bmodule->copy(module);
				bmodule->setSpecies(species);
			}

			modules.put(module->getModuleName(), dcomp);
		}
	} else {
		ManagedReference<DroidComponent*> dcomp = (this->getZoneServer()->createObject(crc, 1)).castTo<DroidComponent*>();
		dcomp->setParent(nullptr);

		BaseDroidModuleComponent* bmodule = cast<BaseDroidModuleComponent*>(dcomp->getDataObjectComponent()->get());

		if (bmodule != nullptr) {
			bmodule->copy(module);
			bmodule->setSpecies(species);
		}

		modules.put(module->getModuleName(), dcomp);
	}
}

void DroidDeedImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();
	while(iterator.hasNext()) {
		ManagedReference<DroidComponent*> comp = iterator.getNextValue();
		if (comp != nullptr)
			comp->destroyObjectFromDatabase(true);
	}

	modules.removeAll();

	DeedImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void DroidDeedImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/*
	 * Values available:	Range:
	 *
	 */
	String key;
	ManagedReference<DroidComponent*> comp = nullptr;
	HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();
	for(int i = 0; i < modules.size(); ++i) {
		iterator.getNextKeyAndValue(key, comp);
		if (comp) {
			comp->destroyObjectFromWorld(true);
			comp->destroyObjectFromDatabase(true);
		}
	}
	modules.removeAll();

	overallQuality = values->getCurrentPercentage("power_level"); // effectiveness
	if (overallQuality < 0)
		overallQuality = 0.1f;

	combatRating = values->getCurrentValue("cmbt_module");
	if (combatRating < 0)
		combatRating = 0;

	if (combatRating > 600)
		combatRating = 600;

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
			if (component != nullptr) {
				if (component->isSocketCluster()) {
					// pull out the objects
					ManagedReference<SceneObject*> craftingComponents = component->getSlottedObject("crafted_components");
					if(craftingComponents != nullptr) {
						SceneObject* satchel = craftingComponents->getContainerObject(0);
						for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
							ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
							if (sceno != nullptr) {
								// now we have the component used in this socket item
								ManagedReference<DroidComponent*> sub = cast<DroidComponent*>( sceno.get());
								if (sub != nullptr) {
									DataObjectComponentReference* data = sub->getDataObjectComponent();
									BaseDroidModuleComponent* module = nullptr;
									if(data != nullptr && data->get() != nullptr && data->get()->isDroidModuleData() ){
										module = cast<BaseDroidModuleComponent*>(data->get());
									}
									if (module == nullptr) {
										continue;
									}
									processModule(module,sceno->getServerObjectCRC());
								}
							}
						}
					}
				} else {
					DataObjectComponentReference* data = component->getDataObjectComponent();
					BaseDroidModuleComponent* module = nullptr;
					if(data != nullptr && data->get() != nullptr && data->get()->isDroidModuleData() ){
						module = cast<BaseDroidModuleComponent*>(data->get());
					}
					if (module == nullptr) {
						continue;
					}
					processModule(module,tano->getServerObjectCRC());
				}
			}
		}
	}
	// module stacking is completed!
}

void DroidDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isASubChildOf(player))
		menuResponse->addRadialMenuItem(20, 3, "@pet/pet_menu:menu_unpack"); //"Ready Droid Unit"
}

int DroidDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		if (generated || !isASubChildOf(player))
			return 1;

		if (player->isInCombat() || player->isRidingMount() || player->isSwimming() || player->isDead() || player->isIncapacitated()) {
			player->sendSystemMessage("@pet/pet_menu:cant_call"); // "You cannot call this pet right now."
			return 1;
		}

		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");

		if (datapad == nullptr) {
			player->sendSystemMessage("Datapad doesn't exist when trying to generate droid");
			return 1;
		}

		// Check if this will exceed maximum number of droids allowed
		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		int droidsInDatapad = 0;
		int maxStoredDroids = playerManager->getBaseStoredDroids();

		for (int i = 0; i < datapad->getContainerObjectsSize(); i++) {
			Reference<SceneObject*> obj =  datapad->getContainerObject(i).castTo<SceneObject*>();

			if (obj != nullptr && obj->isPetControlDevice()) {
				Reference<PetControlDevice*> petDevice = cast<PetControlDevice*>(obj.get());
				if (petDevice != nullptr && petDevice->getPetType() == PetManager::DROIDPET) {
					droidsInDatapad++;
				}
			}
		}

		if (droidsInDatapad >= maxStoredDroids) {
			player->sendSystemMessage("You have too many droids in your datapad");
			return 1;
		}

		Reference<CreatureManager*> creatureManager = player->getZone()->getCreatureManager();
		if (creatureManager == nullptr)
			return 1;

		CreatureTemplateManager* creatureTemplateManager = CreatureTemplateManager::instance();
		Reference<CreatureTemplate*> creatureTemplate =  creatureTemplateManager->getTemplate(mobileTemplate.hashCode());
		if (creatureTemplate == nullptr) {
			player->sendSystemMessage("wrong droid template;mobileTemplate=[" + mobileTemplate + "]" );
			return 1;
		}

		Reference<PetControlDevice*> controlDevice = (server->getZoneServer()->createObject(controlDeviceObjectTemplate.hashCode(), 1)).castTo<PetControlDevice*>();
		if (controlDevice == nullptr) {
			player->sendSystemMessage("wrong droid control device template " + controlDeviceObjectTemplate);
			return 1;
		}

		Locker locker(controlDevice);

		Reference<CreatureObject*> creatureObject = creatureManager->createCreature(generatedObjectTemplate.hashCode(), true, mobileTemplate.hashCode());
		if (creatureObject == nullptr) {
			controlDevice->destroyObjectFromDatabase(true);
			player->sendSystemMessage("wrong droid templates;mobileTemplate=[" + mobileTemplate + "];generatedObjectTemplate=[" + generatedObjectTemplate + "]");
			return 1;
		}

		Locker clocker(creatureObject, player);

		Reference<DroidObject*> droid = creatureObject.castTo<DroidObject*>();
		if (droid == nullptr) {
			controlDevice->destroyObjectFromDatabase(true);
			creatureObject->destroyObjectFromDatabase(true);
			return 1;
		}

		droid->loadTemplateData(creatureTemplate);
		droid->setCustomObjectName(StringIdManager::instance()->getStringId(*droid->getObjectName()), true);
		droid->createChildObjects();
		droid->setControlDevice(controlDevice);

		float maxHam = DroidMechanics::determineHam(overallQuality, species);
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0) {
				droid->setBaseHAM(i, maxHam, false);
				droid->setHAM(i, maxHam, false);
				droid->setMaxHAM(i, maxHam, false);
			} else {
				droid->setBaseHAM(i, maxHam / 10, false);
				droid->setHAM(i, maxHam / 10, false);
				droid->setMaxHAM(i, maxHam / 10, false);
			}
		}

		// this will change to use stacked modules. we wont care about non droid modules as they aren't needed.
		ManagedReference<SceneObject*> craftingComponentsSatchel = droid->getCraftedComponentsSatchel();

		String key;
		ManagedReference<DroidComponent*> comp = nullptr;
		HashTableIterator<String, ManagedReference<DroidComponent*> > iterator = modules.iterator();

		for (int i = 0; i < modules.size(); ++i) {
			iterator.getNextKeyAndValue(key, comp);
			if (comp != nullptr) {
				if (!craftingComponentsSatchel->transferObject(comp, -1, false)) {
					error("Error transferring droid module from Deed to Object");
				}

				BaseDroidModuleComponent* data = cast<BaseDroidModuleComponent*>(comp->getDataObjectComponent()->get());
				if (data != nullptr)
					data->initialize(droid);
			}
		}

		modules.removeAll();

		// Create our transient modules based on the stored physical components
		droid->initDroidModules();
		droid->initDroidWeapons();

		// Copy color customization from deed to droid
		CustomizationVariables* customVars = getCustomizationVariables();
		if (customVars != nullptr) {
			for (int i = 0; i < customVars->size(); ++i) {
				uint8 id = customVars->elementAt(i).getKey();
				int16 val = customVars->elementAt(i).getValue();

				String name = CustomizationIdManager::instance()->getCustomizationVariable(id);

				if (name.contains("color")) {
					droid->setCustomizationVariable(name, val, true);
				}
			}

			droid->refreshPaint();
		}

		StringId s;
		s.setStringId(droid->getObjectName()->getFullPath());
		controlDevice->setObjectName(s, false);
		controlDevice->setPetType(PetManager::DROIDPET);
		controlDevice->setMaxVitality(100);
		controlDevice->setVitality(100);
		controlDevice->setControlledObject(droid);
		controlDevice->setDefaultCommands();

		if (!datapad->transferObject(controlDevice, -1)) {
			controlDevice->destroyObjectFromDatabase(true);
			return 1;
		}

		datapad->broadcastObject(controlDevice, true);

		controlDevice->callObject(player);

		//Remove the deed from its container.
		ManagedReference<SceneObject*> deedContainer = getParent().get();

		if (deedContainer != nullptr) {
			destroyObjectFromWorld(true);
		}

		generated = true;
		destroyObjectFromDatabase(true);

		player->sendSystemMessage("@pet/pet_menu:device_added"); // "A control device has been added to your datapad."
		return 0;
	}

	return DeedImplementation::handleObjectMenuSelect(player, selectedID);
}
