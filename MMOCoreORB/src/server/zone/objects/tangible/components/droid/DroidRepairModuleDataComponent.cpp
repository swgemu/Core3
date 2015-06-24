/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidRepairModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/creature/PetManager.h"

DroidRepairModuleDataComponent::DroidRepairModuleDataComponent() {
	setLoggingName("DroidRepairModule");
}
DroidRepairModuleDataComponent::~DroidRepairModuleDataComponent() {

}
String DroidRepairModuleDataComponent::getModuleName() {
	return String("repair_module");
}
void DroidRepairModuleDataComponent::initializeTransientMembers() {
	// no op
}

void DroidRepairModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "repair_module", "Installed" );
}

void DroidRepairModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, REPAIR_MODULE_ACTIVATE, 3, "Repair" );

	// Add to Program subradial from PetMenuComponent
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == NULL)
		return;
	// converse droid can not have their repair command changed. droids without a personality chip are considered base and get all normal radials
	if (droid->getOptionsBitmask() & OptionBitmask::CONVERSE)
		return;
	menuResponse->addRadialMenuItemToRadialID(141, REPAIR_MODULE_TRAIN, 3, "@pet/pet_menu:menu_repair_other" ); // "Repair Other Droid"
}

int DroidRepairModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle repair request
	if( selectedID == REPAIR_MODULE_ACTIVATE ){

		PetManager* petManager = player->getZoneServer()->getPetManager();
		if( petManager == NULL )
			return 0;

		petManager->enqueuePetCommand(player, getDroidObject(), String("petRepair").toLowerCase().hashCode(), "");

	}
	// Handle command training
	else if( selectedID == REPAIR_MODULE_TRAIN ){

		if( controller == NULL )
			return 0;

		Locker controllerLocker(controller);
		controller->setTrainingCommand( PetManager::REPAIR );

	}

	return 0;
}

void DroidRepairModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL )
		return;

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if( pcd == NULL )
		return;

	PetManager* petManager = droid->getZoneServer()->getPetManager();
	if( petManager == NULL )
		return;

	// Owner-only command
	if( droid->getLinkedCreature() != speaker )
		return;

	if( petManager->isTrainedCommand( pcd, PetManager::REPAIR, cmd ) ){
		petManager->enqueuePetCommand(speaker, droid, STRING_HASHCODE("petrepair"), "");
	}
}

int DroidRepairModuleDataComponent::getBatteryDrain() {
	return 0;  // No constant drain, but each activation will use power
}

String DroidRepairModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
