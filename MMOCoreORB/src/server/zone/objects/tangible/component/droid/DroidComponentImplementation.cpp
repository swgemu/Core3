/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/tangible/components/droid/BaseDroidModuleComponent.h"

void DroidComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();
}

void DroidComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	quality = values->getCurrentValue("mechanism_quality");
	durability = values->getCurrentValue("decayrate");

	// Setup droid module floats for more precise crafting
	autoRepairPower = values->getCurrentValue("auto_repair_power");
	combatRating = values->getCurrentValue("cmbt_module");
	detonationRating = values->getCurrentValue("bomb_level");
	harvestBonus = values->getCurrentValue("harvest_power");
	stimpackSpeed = values->getCurrentValue("stimpack_speed");
	trapBonus = values->getCurrentValue("trap_bonus");

	if (values->hasExperimentalAttribute("droid_count")) {
		setUseCount(values->getCurrentValue("droid_count"));
		surveyDroid = true;
	} else if (autoRepairPower > 0) {
		autoRepairDroid = true;
	} else if (combatRating > 0) {
		combatDroid = true;
	} else if (detonationRating > 0) {
		detonationDroid = true;
	} else if (harvestBonus > 0) {
		harvestDroid = true;
	} else if (stimpackSpeed > 0) {
		stimpackDroid = true;
	} else if (trapBonus > 0) {
		trapDroid = true;
	}

	DataObjectComponentReference* data = getDataObjectComponent();

	if(data != nullptr && data->get() != nullptr && data->get()->isDroidModuleData() ){
		BaseDroidModuleComponent* module = cast<BaseDroidModuleComponent*>(data->get());
		if( module != nullptr ){
			module->updateCraftingValues( values, firstUpdate );
		}
	}
}
void DroidComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	if (autoRepairDroid) {
		alm->insertAttribute("auto_repair_power", (int)autoRepairPower);
	} else if (combatDroid) {
		alm->insertAttribute("cmbt_module", (int)combatRating);
	} else if (detonationDroid) {
		alm->insertAttribute("bomb_level", (int)detonationRating);
	} else if (harvestDroid) {
		alm->insertAttribute("harvest_power", (int)harvestBonus);
	} else if (stimpackDroid) {
		alm->insertAttribute("stimpack_speed", (int)stimpackSpeed);
	} else if (surveyDroid) {
		alm->insertAttribute("decayrate", (int)durability);
		alm->insertAttribute("mechanism_quality", (int)quality);
	} else if (trapDroid) {
		alm->insertAttribute("trap_bonus", (int)trapBonus);
	} else {
		ComponentImplementation::fillAttributeList(alm,object);

		// if a socket cluster, add the cluster items
		if (isSocketCluster()) {
			ManagedReference<SceneObject*> craftingComponents = getSlottedObject("crafted_components");

			if(craftingComponents != nullptr) {
				SceneObject* satchel = craftingComponents->getContainerObject(0);

				// remove all items from satchel and add new items
				for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
					ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);

					// if droid component and a data module add it
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
						module->fillAttributeList(alm,object);
					}
				}
			}
		}
	}
}
bool DroidComponentImplementation::isSocketCluster() {
	String objTemplate = getObjectTemplate()->getFullTemplateString();
	return objTemplate.contains("socket_bank");
}
