/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidHarvestModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/events/DroidHarvestTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/creature/sui/SelectHarvestTypeSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

DroidHarvestModuleDataComponent::DroidHarvestModuleDataComponent() {
	harvestBonus = 0;
	interest = 0; // random
	active = false;
	setLoggingName("DroidHarvestModule");
	harvestTargets.removeAll(0, 10);
}

DroidHarvestModuleDataComponent::~DroidHarvestModuleDataComponent() {
}

String DroidHarvestModuleDataComponent::getModuleName() const {
	return String("harvest_module");
}

void DroidHarvestModuleDataComponent::initializeTransientMembers() {
	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == nullptr) {
		info("droidComponent was null");
		return;
	}

	if (droidComponent->hasKey("harvest_power")) {
		harvestBonus = droidComponent->getAttributeValue("harvest_power");
	} else {
		info("harvest_power attribute not found");
	}

	harvestTargets.removeAll(0, 10);
}

void DroidHarvestModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	harvestBonus = values->getCurrentValue("harvest_power");
}

void DroidHarvestModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute("harvest_power", harvestBonus);
	if (interest == INTEREST_BONE)
		alm->insertAttribute("pet_command_21", "@pet/droid_modules:interest_set_bone");
	if (interest == INTEREST_MEAT)
		alm->insertAttribute("pet_command_21", "@pet/droid_modules:interest_set_meat");
	if (interest == INTEREST_HIDE)
		alm->insertAttribute("pet_command_21", "@pet/droid_modules:interest_set_hide");
	if (interest == INTEREST_RANDOM)
		alm->insertAttribute("pet_command_21", "@pet/droid_modules:interest_set_random");
}

void DroidHarvestModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	// add top level optins
	// then the sub menus
	// multiple levels
	if (player->hasSkill("outdoors_scout_novice")) {
		menuResponse->addRadialMenuItem(HARVEST_MENU, 3, "@pet/droid_modules:harvest_options");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU, HARVEST_PROGRAM_COMMAND, 3, "@pet/droid_modules:program_target_harvest");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU, HARVEST_TOGGLE, 3, "@pet/droid_modules:toggle_auto_harvest");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU, HARVEST_SET_INTEREST, 3, "@pet/droid_modules:set_harvest_interest");
	}
	// menuResponse->addRadialMenuItemToRadialID(132, AUTO_REPAIR_MODULE_TOGGLE, 3, "@pet/droid_modules:harvest_options" );
}

void DroidHarvestModuleDataComponent::setHarvestInterest(CreatureObject* player, int option) {
	interest = option;
	if (option == INTEREST_BONE) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_bone");
	}
	if (option == INTEREST_MEAT) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_meat");
	}
	if (option == INTEREST_HIDE) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_hide");
	}
	if (option == INTEREST_RANDOM) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_random");
	}
}

int DroidHarvestModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {
	if (selectedID == HARVEST_SET_INTEREST) {
		ManagedReference<DroidObject*> droid = getDroidObject();
		if (droid == nullptr) {
			return 0;
		}

		if (!droid->hasPower()) {
			player->sendSystemMessage("@pet/droid_modules:playback_msg_play_out_of_power");
			return 0;
		}

		// popup a ui to choose the correct interest.
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::DROID_SET_INTEREST, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new SelectHarvestSuiCallback(player->getZoneServer()));
		box->setPromptText("@pet/droid_modules:set_interest_d");
		box->setPromptTitle("@pet/droid_modules:set_interest_d");
		box->setOkButton(true, "@ok");
		box->setCancelButton(true, "@cancel");
		// Add tracks
		box->addMenuItem("@pet/droid_modules:set_interest_random", INTEREST_RANDOM);
		box->addMenuItem("@pet/droid_modules:set_interest_bone", INTEREST_BONE);
		box->addMenuItem("@pet/droid_modules:set_interest_meat", INTEREST_MEAT);
		box->addMenuItem("@pet/droid_modules:set_interest_hide", INTEREST_HIDE);
		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());
		return 0;

	} else if (selectedID == HARVEST_PROGRAM_COMMAND) { // Handle toggle on/off
		if (controller == nullptr)
			return 0;

		Locker locker(controller);

		controller->setTrainingCommand(PetManager::HARVEST);
		return 0;

	} else if (selectedID == HARVEST_TOGGLE) {
		ManagedReference<DroidObject*> droid = getDroidObject();

		if (droid == nullptr) {
			return 0;
		}

		Locker dlock(droid, player);

		// Toggle off
		if (active) {
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:auto_harvest_off"); // Auto Harvest: Off
		} else { // Toggle on
			// Check droid states
			if (droid->isDead() || droid->isIncapacitated())
				return 0;

			// Droid must have power
			if (!droid->hasPower()) {
				droid->showFlyText("npc_reaction/flytext", "low_power", 204, 0, 0); // "*Low Power*"
				return 0;
			}

			// Ensure we don't accidentally have another task outstanding
			deactivate();

			player->sendSystemMessage("@pet/droid_modules:auto_harvest_on"); // Auto Harvest: On

			if (observer == nullptr) {
				observer = new DroidHarvestObserver(this);
				observer->deploy();
			}

			Locker plock(player);
			player->registerObserver(ObserverEventType::KILLEDCREATURE, observer);
			active = true;
		}
	}
	return 0;
}

int DroidHarvestModuleDataComponent::getBatteryDrain() {
	if (active) {
		return 4;
	}

	return 0;
}

void DroidHarvestModuleDataComponent::deactivate() {
	active = false;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		return;
	}

	Locker dlock(droid);

	// remove observer
	ManagedReference<CreatureObject*> player = droid->getLinkedCreature().get();

	if (player != nullptr) {
		Locker clock(player, droid);
		player->dropObserver(ObserverEventType::KILLEDCREATURE, observer);
		droid->dropObserver(ObserverEventType::DESTINATIONREACHED, observer);
	}
	if (droid->getPendingTask("droid_harvest")) {
		droid->removePendingTask("droid_harvest");
	}
	harvestTargets.removeAll(0, 10);
}

String DroidHarvestModuleDataComponent::toString() const {
	return BaseDroidModuleComponent::toString();
}

void DroidHarvestModuleDataComponent::onCall() {
	deactivate();

	ManagedReference<DroidObject*> droid = getDroidObject();

	if (droid == nullptr) {
		return;
	}

	if (observer == nullptr) {
		observer = new DroidHarvestObserver(this);
		observer->deploy();
	}

	Locker dlock(droid);

	// add observer for the droid
	// droid->registerObserver(ObserverEventType::DESTINATIONREACHED, observer);
	Reference<Task*> task = new DroidHarvestTask(this);
	droid->addPendingTask("droid_harvest", task, 1000); // 1 sec
}

void DroidHarvestModuleDataComponent::onStore() {
	deactivate();
}

void DroidHarvestModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidHarvestModuleDataComponent* otherModule = cast<DroidHarvestModuleDataComponent*>(other);
	if (otherModule == nullptr)
		return;

	harvestBonus = harvestBonus + otherModule->harvestBonus;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent == nullptr)
		return;
	droidComponent->changeAttributeValue("harvest_power", harvestBonus);
}

void DroidHarvestModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidHarvestModuleDataComponent* otherModule = cast<DroidHarvestModuleDataComponent*>(other);
	if (otherModule == nullptr)
		return;

	harvestBonus = otherModule->harvestBonus;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == nullptr)
		return;
	droidComponent->addProperty("harvest_power", harvestBonus, 0, "exp_effectiveness");
}
void DroidHarvestModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker) {
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		return;
	}

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if (pcd == nullptr) {
		return;
	}

	PetManager* petManager = droid->getZoneServer()->getPetManager();
	if (petManager == nullptr) {
		return;
	}

	// Owner-only command
	if (droid->getLinkedCreature().get() != speaker) {
		return;
	}

	if (petManager->getTrainedCommandNum(pcd, cmd) == PetManager::HARVEST) {
		Locker dlock(droid);
		uint64 targetID = speaker->getTargetID();
		Reference<CreatureObject*> target = droid->getZoneServer()->getObject(targetID, true).castTo<CreatureObject*>();

		if (target != nullptr) {
			// this check should occur in the pet speaking handling.
			if (!target->isInRange(droid, 64)) {
				speaker->sendSystemMessage("@pet/droid_modules:corpse_too_far");
				return;
			}

			harvestTargets.add(targetID);
		}
		for (int i = 0; i < harvestTargets.size(); i++) {
			if (harvestTargets.get(i) == targetID)
				return;
		}
		harvestTargets.add(targetID);
	}
}
void DroidHarvestModuleDataComponent::creatureHarvestCheck(CreatureObject* target) {
	if (!active)
		return;
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == nullptr) {
		return;
	}
	if (target == nullptr) {
		return;
	}
	if (!target->isCreature()) {
		return;
	}
	uint64 targetID = target->getObjectID();
	// add to target list, call command
	for (int i = 0; i < harvestTargets.size(); i++) {
		if (harvestTargets.get(i) == targetID)
			return;
	}
	harvestTargets.add(targetID);
}
void DroidHarvestModuleDataComponent::harvestDestinationReached() {
	// No-Op
}
