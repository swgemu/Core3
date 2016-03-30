/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidDataStorageModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

DroidDataStorageModuleDataComponent::DroidDataStorageModuleDataComponent() {
	setLoggingName("DroidDataStorageModule");
	rating = 0;
}

DroidDataStorageModuleDataComponent::~DroidDataStorageModuleDataComponent() {

}

String DroidDataStorageModuleDataComponent::getModuleName() {
	return String("datapad_storage_module");
}

void DroidDataStorageModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if (droidComponent->hasKey("data_module")) {
		rating = droidComponent->getAttributeValue("data_module");
	}
}

void DroidDataStorageModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("data_module");
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

void DroidDataStorageModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute("data_module", rating > 10 ? 10 : rating);
}

String DroidDataStorageModuleDataComponent::toString() {
	return BaseDroidModuleComponent::toString();
}

void DroidDataStorageModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidDataStorageModuleDataComponent* otherModule = cast<DroidDataStorageModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	rating = rating + otherModule->rating;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->changeAttributeValue("data_module", (float)rating);
}

void DroidDataStorageModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidDataStorageModuleDataComponent* otherModule = cast<DroidDataStorageModuleDataComponent*>(other);
	if (otherModule == NULL)
		return;

	rating = otherModule->rating;

	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->addProperty("data_module", (float)rating, 0, "exp_effectiveness");
}

void DroidDataStorageModuleDataComponent::onCall() {
	// no op
}

void DroidDataStorageModuleDataComponent::onStore() {
	// no op on store
}

void DroidDataStorageModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, DATA_STORAGE_MODULE_OPEN, 3, "@pet/pet_menu:menu_dpad");
}

void DroidDataStorageModuleDataComponent::initialize(DroidObject* droid) {
	StringBuffer path;
	path.append("object/tangible/datapad/droid_datapad_");
	path.append(getStorageRating());
	path.append(".iff");

	ManagedReference<SceneObject*> inventory = droid->getZoneServer()->createObject(path.toString().hashCode(), 1);
	if (inventory == NULL) {
		return;
	}

	ManagedReference<SceneObject*> droidInvorty = droid->getSlottedObject("datapad");
	if (droidInvorty) {
		droid->removeObject(droidInvorty, NULL, true);
		droidInvorty->destroyObjectFromDatabase(true);
	}

	if (!droid->transferObject(inventory, 4, true)) {
		inventory->destroyObjectFromDatabase(true);
	}
}

int DroidDataStorageModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle open droid storage
	if (selectedID == DATA_STORAGE_MODULE_OPEN) {

		ManagedReference<DroidObject*> droid = getDroidObject();
		if (droid == NULL) {
			info( "Droid is null");
			return 0;
		}

		Locker dlock (droid, player);

		// open the inventory slot of the droid
		ManagedReference<SceneObject*> inventory = droid->getSlottedObject("datapad");

		if (inventory != NULL) {
			inventory->openContainerTo(player);
		}
	}

	return 0;
}
