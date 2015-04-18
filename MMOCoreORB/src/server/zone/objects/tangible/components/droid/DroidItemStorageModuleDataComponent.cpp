/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidItemStorageModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

DroidItemStorageModuleDataComponent::DroidItemStorageModuleDataComponent() {
	setLoggingName("DroidItemStorageModule");
	rating = 0;
}
DroidItemStorageModuleDataComponent::~DroidItemStorageModuleDataComponent() {

}
String DroidItemStorageModuleDataComponent::getModuleName() {
	return String("item_storage_module");
}
void DroidItemStorageModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "storage_module")) {
		rating = droidComponent->getAttributeValue( "storage_module");
	}
}
void DroidItemStorageModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("storage_module");
}
int DroidItemStorageModuleDataComponent::getStorageRating() {
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
void DroidItemStorageModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "storage_module", rating > 10 ? 10 : rating );
}
String DroidItemStorageModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidItemStorageModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidItemStorageModuleDataComponent* otherModule = cast<DroidItemStorageModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = rating + otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->changeAttributeValue("storage_module",(float)rating);
}
void DroidItemStorageModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidItemStorageModuleDataComponent* otherModule = cast<DroidItemStorageModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->addProperty("storage_module",(float)rating,0,"exp_effectiveness");
}
void DroidItemStorageModuleDataComponent::onCall() {
	// no op
}
void DroidItemStorageModuleDataComponent::onStore() {
	// no op on store
}
void DroidItemStorageModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, ITEM_STORAGE_MODULE_OPEN, 3, "@pet/pet_menu:menu_command_open" );
}
void DroidItemStorageModuleDataComponent::initialize(CreatureObject* droid) {
	StringBuffer path;
	path.append("object/tangible/inventory/creature_inventory_");
	path.append(getStorageRating());
	path.append(".iff");

	ManagedReference<SceneObject*> inventory = droid->getZoneServer()->createObject(path.toString().hashCode(),1);
	if (inventory == NULL) {
		return;
	}

	ManagedReference<SceneObject*> droidInvorty = droid->getSlottedObject("inventory");
	if (droidInvorty) {
		droid->removeObject(droidInvorty,NULL,true);
		droidInvorty->destroyObjectFromDatabase(true);
	}

	if (!droid->transferObject(inventory,4,true)) {
		inventory->destroyObjectFromDatabase(true);
	}

}
int DroidItemStorageModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle open droid storage
	if( selectedID == ITEM_STORAGE_MODULE_OPEN ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );
		// open the inventory slot of the droid
		ManagedReference<SceneObject*> inventory = droid->getSlottedObject("inventory");

		if (inventory != NULL) {
			inventory->openContainerTo(player);
		}
	}
	return 0;
}

