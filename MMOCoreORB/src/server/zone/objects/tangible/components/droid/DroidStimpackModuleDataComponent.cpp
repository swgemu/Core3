/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidStimpackModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/creature/events/DroidStimpackTask.h"
#include "server/zone/objects/creature/sui/LoadStimpackSuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/PlayerObject.h"

DroidStimpackModuleDataComponent::DroidStimpackModuleDataComponent() {
	setLoggingName("DroidStimpackModule");
	speed = 0;
	capacity = 0;
	rate = 0;
	loaded = 0;
}

DroidStimpackModuleDataComponent::~DroidStimpackModuleDataComponent() {

}

String DroidStimpackModuleDataComponent::getModuleName() {
	return String("stimpack_module");
}

void DroidStimpackModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if (droidComponent->hasKey( "stimpack_capacity")) {
		capacity = droidComponent->getAttributeValue("stimpack_capacity");
	}

	if (droidComponent->hasKey("stimpack_speed")) {
		speed = droidComponent->getAttributeValue("stimpack_speed");
	}
}

void DroidStimpackModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	capacity = values->getCurrentValue("stimpack_capacity");
	speed = values->getCurrentValue("stimpack_speed");
}

void DroidStimpackModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	StringBuffer sb;
	sb << loaded;
	sb << "/";
	sb << capacity;

	alm->insertAttribute("stimpack_capacity", sb.toString());
	alm->insertAttribute("stimpack_speed", speed);

	float power = 0;

	if (loaded > 0) {
		StimPack* sp = findStimPack();

		if (sp != NULL)
			power = sp->getEffectiveness();
	}

	alm->insertAttribute("stimpack_power", power);
}

String DroidStimpackModuleDataComponent::toString() {
	return BaseDroidModuleComponent::toString();
}

void DroidStimpackModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidStimpackModuleDataComponent* otherModule = cast<DroidStimpackModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	speed = speed + otherModule->speed;
	capacity = capacity + otherModule->capacity;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent != NULL) {
		droidComponent->changeAttributeValue("stimpack_capacity", (float)capacity);
		droidComponent->changeAttributeValue("stimpack_speed", (float)speed);
	}
}

void DroidStimpackModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidStimpackModuleDataComponent* otherModule = cast<DroidStimpackModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	speed = speed + otherModule->speed;
	capacity = capacity + otherModule->capacity;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent != NULL) {
		droidComponent->addProperty("stimpack_speed", (float)speed, 0, "exp_effectiveness");
		droidComponent->addProperty("stimpack_capacity", (float)capacity, 0, "exp_durability");
	}
}

void DroidStimpackModuleDataComponent::onCall() {
	// recalculate the rate
	if (speed == 0) {
		rate = 60000;
	} else {
		rate = round((float)60 * ((float)1 / (float)speed)) * 1000;
	}

	countUses();
}

StimPack* DroidStimpackModuleDataComponent::compatibleStimpack(float power) {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return NULL;
	}

	DroidObject* droid = getDroidObject();
	if (droid == NULL) {
		return NULL;
	}

	Locker dlock(droid);

	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");

	if (craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		if (satchel == NULL) {
			return NULL;
		}

		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
			SceneObject* item = satchel->getContainerObject(i);
			if (!item->isPharmaceuticalObject())
				continue;

			PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(item);

			if (pharma->isStimPack()) {
				StimPack* stim = cast<StimPack*>(pharma);

				if (stim->getEffectiveness() == power) {
					return stim;
				}
			}
		}
	}

	return NULL;
}

void DroidStimpackModuleDataComponent::countUses() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	DroidObject* droid = getDroidObject();
	if (droid == NULL) {
		return ;
	}

	Locker dlock(droid);

	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if (craftingComponents == NULL) {
		return;
	}

	SceneObject* satchel = craftingComponents->getContainerObject(0);
	if (satchel == NULL) {
		return;
	}

	loaded = 0;

	for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> item = satchel->getContainerObject(i);
		if (!item->isPharmaceuticalObject())
			continue;

		PharmaceuticalObject* pharma = item.castTo<PharmaceuticalObject*>();

		if (pharma->isStimPack())
			loaded += pharma->getUseCount();
	}
}

void DroidStimpackModuleDataComponent::onStore() {
	// no-op
	countUses();
}

/**
 * Add Droid sub-radial options, need to be a top level radial not submenu
 */
void DroidStimpackModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	menuResponse->addRadialMenuItem(REQUEST_STIMPACK, 3, "@pet/droid_modules:request_stimpack" );

	if (player != NULL && player->hasSkill("science_medic_ability_04"))
		menuResponse->addRadialMenuItemToRadialID(REQUEST_STIMPACK, LOAD_STIMPACK, 3, "@pet/droid_modules:load_stimpack" );
}

void DroidStimpackModuleDataComponent::initialize(DroidObject* droid) {
	// grab the crafted components in this module and remove then
	// then change capacity to the new capacity so we store the stims directly in the component.
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	
	//This will instantiate the crafted_components slotted container and satchel if they do not exist
	ManagedReference<SceneObject*> satchel = droidComponent->getCraftedComponentsSatchel();
	if (satchel != NULL) {
		satchel->setContainerVolumeLimit(capacity);
	}

	
}

int DroidStimpackModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	ManagedReference<DroidObject*> droid = getDroidObject();
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droid == NULL || droidComponent == NULL) {
		player->sendSystemMessage("@pet/droid_modules:stimpack_error");
		return 0;
	}
	
	if (selectedID == LOAD_STIMPACK) {
		Locker crossLoker(droid, player);
		
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == NULL) {
			player->sendSystemMessage("@pet/droid_modules:no_stimpacks");
			return 0;
		}

		int foundStims = 0;

		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> item = inventory->getContainerObject(i);

			if (!item->isPharmaceuticalObject())
				continue;

			// check it they have atleast 1 stim pack
			PharmaceuticalObject* pharma = item.castTo<PharmaceuticalObject*>();

			if (pharma->isStimPack()) {
				StimPack* stim = cast<StimPack*>(pharma);

				if (stim->isClassA()) {
					foundStims += 1;
				}
			}
		}

		if (foundStims == 0) {
			player->sendSystemMessage("@pet/droid_modules:no_stimpacks");
			return 0;
		} else {
			sendLoadUI(player);
			return 0;
		}

	} else if (selectedID == REQUEST_STIMPACK) {
		// we need to check cooldown on droid
		if (droid->isDead() || droid->isIncapacitated() || player->isDead()) {
			return 0;
		}

		// Droid must have power
		if (!droid->hasPower()) {
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return 0;
		}

		if (droid->getPendingTask("droid_request_stimpack") != NULL) {
			player->sendSystemMessage("@pet/droid_modules:stimpack_not_ready");
			return 0;
		}

		// Submit stimpack task
		Reference<Task*> task = new DroidStimpackTask( droid,player,controller->getCustomObjectName().toString() );
		droid->addPendingTask("droid_request_stimpack", task, 1); // rte determines when it will fire it
	}

	return 0;
}

void DroidStimpackModuleDataComponent::sendLoadUI(CreatureObject* player) {
	ManagedReference<SceneObject* > inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return;

	ManagedReference<SuiListBox*> loader = new SuiListBox(player, SuiWindowType::DROID_LOAD_STIMPACK, SuiListBox::HANDLETWOBUTTON);
	loader->setPromptTitle("@pet/droid_modules:load_stimpack");
	loader->setPromptText("@group:set_loot_type_text");
	loader->setOkButton(true, "@ok");
	loader->setCancelButton(true, "@cancel");

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		SceneObject* item = inventory->getContainerObject(i);

		if (!item->isPharmaceuticalObject())
			continue;

		// check it they have atleast 1 stim pack
		PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>(item);

		if (pharma->isStimPack()) {
			StimPack* stim = cast<StimPack*>(pharma);

			if (stim->isClassA()) {
				String name;

				if (stim->getCustomObjectName().isEmpty()) {
					name = "@" + stim->getObjectNameStringIdFile() + ":" + stim->getObjectNameStringIdName();
				} else {
					name = stim->getCustomObjectName().toString();
				}

				loader->addMenuItem(name, stim->getObjectID());
			}
		}
	}

	loader->setCallback(new LoadStimpackSuiCallback(getParent()->getZoneServer()));
	loader->setUsingObject(getDroidObject());
	player->getPlayerObject()->addSuiBox(loader);
	player->sendMessage(loader->generateMessage());
}

StimPack* DroidStimpackModuleDataComponent::findStimPack() {
	StimPack* pack = NULL;
	float biggest = 0;
	DroidComponent* container = cast<DroidComponent*>(getParent());

	if (container == NULL)
		return NULL;

	ManagedReference<SceneObject*> craftingComponents = container->getSlottedObject("crafted_components");

	if (craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);

		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);

			// is a stimpack
			if (sceno->isPharmaceuticalObject()) {
				PharmaceuticalObject* pharma = sceno.castTo<PharmaceuticalObject*>();

				if (pharma->isStimPack() && !pharma->isPetStimPack() && !pharma->isDroidRepairKit()) {
					StimPack* stim = cast<StimPack*>(pharma);

					if (stim->getEffectiveness() > biggest) {
						biggest = stim->getEffectiveness();
						pack = stim;
					}
				}
			}
		}
	}

	return pack;
}

void DroidStimpackModuleDataComponent::handleInsertStimpack(CreatureObject* player, StimPack* pack) {
	countUses();

	if (player == NULL)
		return;

	if (!player->hasSkill("science_medic_ability_04")) {
		return;
	}

	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == NULL) {
		return;
	}

	if (pack == NULL) {
		player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
		return;
	}

	if (!pack->isClassA()) {
		player->sendSystemMessage("@pet/droid_modules:invalid_stimpack");
		return;
	}

	if (droid->getLinkedCreature().get() != player) {
		return;
	}

	// we have the player and the stim to add to ourselves.
	// code should goes as follow, count total use of all stims, then deduct amount form capacity
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent == NULL) {
		return;
	}

	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");

	if (craftingComponents == NULL) {
		return;
	}

	SceneObject* satchel = craftingComponents->getContainerObject(0);

	if (satchel == NULL) {
		return;
	}

	int allowedAmount = capacity - loaded;

	if (allowedAmount <= 0) {
		player->sendSystemMessage("@pet/droid_modules:stimpack_capacity_full");
		return;
	}

	Locker plocker(pack);

	int amountOnStim = pack->getUseCount();
	StimPack* targetStim = compatibleStimpack(pack->getEffectiveness());

	if (targetStim != NULL) {
		Locker tlocker(targetStim);

		if (allowedAmount > amountOnStim) {
			targetStim->setUseCount(targetStim->getUseCount() + amountOnStim, true);
			pack->decreaseUseCount(pack->getUseCount());
		} else {
			targetStim->setUseCount(targetStim->getUseCount() + allowedAmount, true);
			pack->decreaseUseCount(allowedAmount);
		}
	} else {
		// can we take it all?
		if (allowedAmount > amountOnStim) {
			pack->destroyObjectFromWorld(true);
			// transfer to the droid and broadcast, then send the satchel to the player
			satchel->transferObject(pack, -1, true);
			satchel->broadcastObject(pack, true);
			pack->sendTo(player, true);
			droid->sendTo(player, true);
			player->sendSystemMessage("@pet/droid_modules:stimpack_loaded");
		} else {
			// we cant load it all so split the diff
			StimPack* newStim = pack->split(allowedAmount);

			if (newStim != NULL) {
				Locker slocker(newStim);
				satchel->transferObject(newStim, -1, true);
				satchel->broadcastObject(newStim, true);
				player->sendSystemMessage("@pet/droid_modules:stimpack_loaded");
			}
		}
	}

	countUses();
}

int DroidStimpackModuleDataComponent::getBatteryDrain() {
	return 0;
}
