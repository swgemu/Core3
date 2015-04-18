/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidAutoRepairModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/events/DroidAutoRepairTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

DroidAutoRepairModuleDataComponent::DroidAutoRepairModuleDataComponent() {
	autoRepairPower = 0;
	active = false;
	setLoggingName("DroidAutoRepairModule");
}
DroidAutoRepairModuleDataComponent::~DroidAutoRepairModuleDataComponent() {

}
String DroidAutoRepairModuleDataComponent::getModuleName() {
	return String("auto_repair_module");
}
void DroidAutoRepairModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if( droidComponent->hasKey( "auto_repair_power") ){
		autoRepairPower = droidComponent->getAttributeValue( "auto_repair_power");
	}
	else{
		info( "auto_repair_power attribute not found" );
	}
}

void DroidAutoRepairModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	autoRepairPower = values->getCurrentValue("auto_repair_power");
}

void DroidAutoRepairModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "auto_repair_power", autoRepairPower );
}

void DroidAutoRepairModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, AUTO_REPAIR_MODULE_TOGGLE, 3, "@pet/droid_modules:toggle_autorepair" );
}

int DroidAutoRepairModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle toggle on/off
	if( selectedID == AUTO_REPAIR_MODULE_TOGGLE ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle off
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:autorepair_off");  // You turn off auto-repair
		}
		// Toggle on
		else{

			// Check droid states
			if( droid->isDead() || droid->isIncapacitated() )
				return 0;

			// Droid must have power
			if( !droid->hasPower() ){
				droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return 0;
			}

			// Ensure we don't accidentally have another task outstanding
			deactivate();

			// Submit repair task
			Reference<Task*> task = new DroidAutoRepairTask( this );
			droid->addPendingTask("droid_auto_repair", task, 10000); // 10 sec
			player->sendSystemMessage("@pet/droid_modules:autorepair_on");  // You turn on auto-repair
			active = true;
		}

	}
	return 0;
}

int DroidAutoRepairModuleDataComponent::getBatteryDrain() {

	if( active ){
		return 4;
	}

	return 0;
}

void DroidAutoRepairModuleDataComponent::deactivate() {

	active = false;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// Cancel auto repair task
	Task* task = droid->getPendingTask( "droid_auto_repair" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "droid_auto_repair" );
	}

}

String DroidAutoRepairModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidAutoRepairModuleDataComponent::onCall(){
	deactivate();
}

void DroidAutoRepairModuleDataComponent::onStore(){
	deactivate();
}

void DroidAutoRepairModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidAutoRepairModuleDataComponent* otherModule = cast<DroidAutoRepairModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	autoRepairPower = autoRepairPower + otherModule->autoRepairPower;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	// Attribute should have already been created in copy method
	if( !droidComponent->changeAttributeValue( "auto_repair_power", autoRepairPower) ){
		info( "addToStack updateAttributeValue failed");
		return;
	}

	info( "addToStack autoRepairPower=" + String::valueOf(autoRepairPower) );
}

void DroidAutoRepairModuleDataComponent::copy(BaseDroidModuleComponent* other){

	DroidAutoRepairModuleDataComponent* otherModule = cast<DroidAutoRepairModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	autoRepairPower = otherModule->autoRepairPower;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	droidComponent->addProperty("auto_repair_power", autoRepairPower, 0, "exp_effectiveness");

	info( "copy autoRepairPower=" + String::valueOf(autoRepairPower) );

}
