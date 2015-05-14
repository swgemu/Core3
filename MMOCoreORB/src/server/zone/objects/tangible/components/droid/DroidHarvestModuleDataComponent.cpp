/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "DroidHarvestModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/events/DroidHarvestTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/intangible/tasks/EnqueuePetCommand.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/creature/sui/SelectHarvestTypeSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

DroidHarvestModuleDataComponent::DroidHarvestModuleDataComponent() {
	harvestBonus = 0;
	interest = 0; // random
	active = false;
	setLoggingName("DroidHarvestModule");
	harvestTargets.removeAll(0,10);
}
DroidHarvestModuleDataComponent::~DroidHarvestModuleDataComponent() {

}
String DroidHarvestModuleDataComponent::getModuleName() {
	return String("harvest_module");
}
void DroidHarvestModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if( droidComponent->hasKey( "harvest_power") ){
		harvestBonus = droidComponent->getAttributeValue( "harvest_power");
	}
	else{
		info( "harvest_power attribute not found" );
	}
	harvestTargets.removeAll(0,10);
}

void DroidHarvestModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	harvestBonus = values->getCurrentValue("harvest_power");
}

void DroidHarvestModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "harvest_power", harvestBonus );
	if (interest == INTREST_BONE)
		alm->insertAttribute("pet_command_21","@pet/droid_modules:interest_set_bone");
	if (interest == INTREST_MEAT)
		alm->insertAttribute("pet_command_21","@pet/droid_modules:interest_set_meat");
	if (interest == INTREST_HIDE)
		alm->insertAttribute("pet_command_21","@pet/droid_modules:interest_set_hide");
	if (interest == INTREST_RANDOM)
		alm->insertAttribute("pet_command_21","@pet/droid_modules:interest_set_random");
}

void DroidHarvestModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	// add top level optins
	// then the sub menus
	// multiple levels
	if (player->hasSkill("outdoors_scout_novice")){
		menuResponse->addRadialMenuItem(HARVEST_MENU,3,"@pet/droid_modules:harvest_options");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU,HARVEST_PROGRAM_COMMAND,3, "@pet/droid_modules:program_target_harvest");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU,HARVEST_TOGGLE,3,"@pet/droid_modules:toggle_auto_harvest");
		menuResponse->addRadialMenuItemToRadialID(HARVEST_MENU,HARVEST_SET_INTEREST,3,"@pet/droid_modules:set_harvest_interest");
	}
	//menuResponse->addRadialMenuItemToRadialID(132, AUTO_REPAIR_MODULE_TOGGLE, 3, "@pet/droid_modules:harvest_options" );
}
void DroidHarvestModuleDataComponent::setHarvestInterest(CreatureObject* player, int option) {
	interest = option;
	if (option == INTREST_BONE) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_bone");
	}
	if (option == INTREST_MEAT) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_meat");
	}
	if (option == INTREST_HIDE) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_hide");
	}
	if (option == INTREST_RANDOM) {
		player->sendSystemMessage("@pet/droid_modules:interest_set_random");
	}

}
int DroidHarvestModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	if (selectedID == HARVEST_SET_INTEREST) {
		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		if( !droid->hasPower() ){
			player->sendSystemMessage("@pet/droid_modules:playback_msg_play_out_of_power");
			return 0;
		}

		// popup a ui to choose the correct interest.
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::DROID_SET_INTEREST, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new SelectHarvestSuiCallback(player->getZoneServer()));
		box->setPromptText("@pet/droid_modules:set_interest_d");
		box->setPromptTitle("@pet/droid_modules:set_interest_d");
		box->setOkButton(true,"@ok");
		box->setCancelButton(true, "@cancel");
		// Add tracks
		box->addMenuItem("@pet/droid_modules:set_interest_random",INTREST_RANDOM);
		box->addMenuItem("@pet/droid_modules:set_interest_bone",INTREST_BONE);
		box->addMenuItem("@pet/droid_modules:set_interest_meat",INTREST_MEAT);
		box->addMenuItem("@pet/droid_modules:set_interest_hide",INTREST_HIDE);
		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());
		return 0;
	}
	// Handle toggle on/off
	if (selectedID == HARVEST_PROGRAM_COMMAND) {
		if( controller == NULL )
			return 0;
		controller->setTrainingCommand( PetManager::HARVEST );
		return 0;
	}
	if( selectedID == HARVEST_TOGGLE ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle off
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:auto_harvest_off");  // You turn off auto-repair
		}
		else{ // Toggle on

			// Check droid states
			if( droid->isDead() || droid->isIncapacitated())
				return 0;

			// Droid must have power
			if( !droid->hasPower() ){
				droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return 0;
			}

			// Ensure we don't accidentally have another task outstanding
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:auto_harvest_on");  // You turn on auto-repair
			if (observer == NULL) {
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

	if( active ){
		return 4;
	}

	return 0;
}

void DroidHarvestModuleDataComponent::deactivate() {

	active = false;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// remove observer
	ManagedReference<CreatureObject*> player = droid->getLinkedCreature().get();

	if (player != NULL) {
		Locker clock(player, droid);
		player->dropObserver(ObserverEventType::KILLEDCREATURE, observer);
		droid->dropObserver(ObserverEventType::DESTINATIONREACHED, observer);
	}
	if(droid->getPendingTask("droid_harvest")) {
		droid->removePendingTask("droid_harvest");
	}
	harvestTargets.removeAll(0,10);
}

String DroidHarvestModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidHarvestModuleDataComponent::onCall(){
	deactivate();
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null");
		return;
	}
	if (observer == NULL) {
		observer = new DroidHarvestObserver(this);
		observer->deploy();
	}
	Locker dlock( droid );
	// add observer for the droid
	//droid->registerObserver(ObserverEventType::DESTINATIONREACHED, observer);
	Reference<Task*> task = new DroidHarvestTask( this );
	droid->addPendingTask("droid_harvest", task, 1000); // 1 sec
}

void DroidHarvestModuleDataComponent::onStore(){
	deactivate();
}

void DroidHarvestModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidHarvestModuleDataComponent* otherModule = cast<DroidHarvestModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	harvestBonus = harvestBonus + otherModule->harvestBonus;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;
	droidComponent->changeAttributeValue( "harvest_power", harvestBonus);

}

void DroidHarvestModuleDataComponent::copy(BaseDroidModuleComponent* other){

	DroidHarvestModuleDataComponent* otherModule = cast<DroidHarvestModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	harvestBonus = otherModule->harvestBonus;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;
	droidComponent->addProperty("harvest_power", harvestBonus, 0, "exp_effectiveness");
}
void DroidHarvestModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		return;
	}

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if( pcd == NULL ) {
		return;
	}

	PetManager* petManager = droid->getZoneServer()->getPetManager();
	if( petManager == NULL ) {
		return;
	}

	// Owner-only command
	if( droid->getLinkedCreature().get() != speaker ) {
		return;
	}

	if( petManager->isTrainedCommand( pcd, PetManager::HARVEST, cmd ) ){
		Locker dlock(droid);
		uint64 targetID = speaker->getTargetID();
		Reference<CreatureObject*> target = droid->getZoneServer()->getObject(targetID, true).castTo<CreatureObject*>();
		// this check should occur in the pet speaking handling.
		if(!target->isInRange(droid,64)) {
			speaker->sendSystemMessage("@pet/droid_modules:corpse_too_far");
			return;
		}
		harvestTargets.add(targetID);
	}
}
void DroidHarvestModuleDataComponent::creatureHarvestCheck(CreatureObject* target) {
	if(!active)
		return;
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL){
		return;
	}
	if(target == NULL) {
		return;
	}
	if(!target->isCreature()) {
		return;
	}
	// add to target list, call command
	harvestTargets.add(target->getObjectID());
}
void DroidHarvestModuleDataComponent::harvestDestinationReached() {
	// No-Op
}
