/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidDataStorageModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

DroidDataStorageModuleDataComponent::DroidDataStorageModuleDataComponent() {
	setLoggingName("DroidDataStorageModule");
	rating = 0;
}

DroidDataStorageModuleDataComponent::~DroidDataStorageModuleDataComponent() {

}

// This function is called when new droids are initialized from their deed containing a data storage module
void DroidDataStorageModuleDataComponent::initialize(DroidObject* droid) {
	if (droid == nullptr) {
		return;
	}

	auto zoneServer = droid->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	auto controlDevice = droid->getControlDevice().get();

	if (controlDevice == nullptr || !controlDevice->isPetControlDevice()) {
		return;
	}

	// Control device will store the droids datapad & is already locked in the calling function in DroidDeedImplementation
	auto droidControlDevice = controlDevice.castTo<PetControlDevice*>();

	if (droidControlDevice == nullptr) {
		return;
	}

	StringBuffer path;
	path << "object/tangible/datapad/droid_datapad_"  << getStorageRating() << ".iff";

	ManagedReference<SceneObject*> droidDatapad = zoneServer->createObject(path.toString().hashCode(), 1);

	if (droidDatapad == nullptr) {
		return;
	}

	// Check for a current datapad
	ManagedReference<SceneObject*> currentDatapad = droidControlDevice->getDatapad();

	// Current datapad should not exist on new modules, just in case destroy it
	if (currentDatapad != nullptr) {
		Locker clock(currentDatapad, droid);

		droid->removeObject(currentDatapad, nullptr, true);
		currentDatapad->destroyObjectFromDatabase(true);
	}

	Locker deviceClock(droidDatapad, droid);

	// Transfer in the droid datapad into the control device
	if (!droidControlDevice->transferObject(droidDatapad, PlayerArrangement::RIDER, true)) {
		droidDatapad->destroyObjectFromDatabase(true);
	}
}

void DroidDataStorageModuleDataComponent::initializeTransientMembers() {
	auto parentScene = getParent();

	if (parentScene == nullptr) {
		return;
	}

	DroidComponent* droidComponent = cast<DroidComponent*>(parentScene);

	if (droidComponent != nullptr && droidComponent->hasKey("data_module")) {
		rating = droidComponent->getAttributeValue("data_module");
	}

	// Handle conversion by moving olds datapad onto PCD
	auto droid = parentScene->getParentRecursively(SceneObjectType::DROIDCREATURE).castTo<CreatureObject*>();

	if (droid == nullptr) {
		return;
	}

	auto controlDevice = droid->getControlDevice().castTo<PetControlDevice*>();

	if (controlDevice == nullptr || controlDevice->getDatapad() != nullptr) {
		return;
	}

	auto oldDatapad = droid->getDatapad();

	if (oldDatapad == nullptr) {
		return;
	}

	Locker lock(controlDevice);
	Locker clock(oldDatapad, controlDevice);

	if (!controlDevice->transferObject(oldDatapad, PlayerArrangement::RIDER)) {
		return;
	}

	// Run the update for this object
	controlDevice->updateToDatabase();
}

void DroidDataStorageModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("data_module");
}

void DroidDataStorageModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute("data_module", rating > 10 ? 10 : rating);
}

void DroidDataStorageModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidDataStorageModuleDataComponent* otherModule = cast<DroidDataStorageModuleDataComponent*>(other);

	if (otherModule == nullptr) {
		return;
	}

	rating = rating + otherModule->rating;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent != nullptr) {
		droidComponent->changeAttributeValue("data_module", (float)rating);
	}
}

void DroidDataStorageModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidDataStorageModuleDataComponent* otherModule = cast<DroidDataStorageModuleDataComponent*>(other);

	if (otherModule == nullptr) {
		return;
	}

	rating = otherModule->rating;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());

	if (droidComponent != nullptr) {
		droidComponent->addProperty("data_module", (float)rating, 0, "exp_effectiveness");
	}
}

void DroidDataStorageModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, DATA_STORAGE_MODULE_OPEN, 3, "@pet/pet_menu:menu_dpad");
}

int DroidDataStorageModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* petControlDevice) {
	if (player == nullptr || petControlDevice == nullptr) {
		return 0;
	}

	// Handle open droid storage
	if (selectedID == DATA_STORAGE_MODULE_OPEN) {
		// open the datapad to the player
		ManagedReference<SceneObject*> droidDatapad = petControlDevice->getDatapad();

		if (droidDatapad != nullptr) {
			droidDatapad->openContainerTo(player);
		}
	}

	return 0;
}

int DroidDataStorageModuleDataComponent::getStorageRating() {
	switch(rating) {
		case 1:
		case 2:
			return 1;
		case 3:
		case 4:
			return 2;
		case 5:
		case 6:
			return 3;
		case 7:
		case 8:
			return 4;
		case 9:
		case 10:
			return 5;
	}

	return 6;
}

String DroidDataStorageModuleDataComponent::getModuleName() const {
	return String("datapad_storage_module");
}

String DroidDataStorageModuleDataComponent::toString() const {
	return BaseDroidModuleComponent::toString();
}

void DroidDataStorageModuleDataComponent::onCall() {
	// no op
}

void DroidDataStorageModuleDataComponent::onStore() {
	// no op on store
}
