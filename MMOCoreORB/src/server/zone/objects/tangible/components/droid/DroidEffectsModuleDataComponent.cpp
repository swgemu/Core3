/*
 * Copyright (C) 2014 <SWGEmu>
 * This File is part of Core3.
 * This program is free software; you can redistribute
 * it and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program; if not, write to
 * the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Linking Engine3 statically or dynamically with other modules
 * is making a combined work based on Engine3.
 * Thus, the terms and conditions of the GNU Lesser General Public License
 * cover the whole combination.
 *
 * In addition, as a special exception, the copyright holders of Engine3
 * give you permission to combine Engine3 program with free software
 * programs or libraries that are released under the GNU LGPL and with
 * code included in the standard release of Core3 under the GNU LGPL
 * license (or modified versions of such code, with unchanged license).
 * You may copy and distribute such a system following the terms of the
 * GNU LGPL for Engine3 and the licenses of the other code concerned,
 * provided that you include the source code of that other code when
 * and as the GNU LGPL requires distribution of source code.
 *
 * Note that people who make modified versions of Engine3 are not obligated
 * to grant this special exception for their modified versions;
 * it is their choice whether to do so. The GNU Lesser General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 */

#include "DroidEffectsModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/objects/creature/events/DroidEffectsTask.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/DroidEffectsModuleTemplate.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/SelectDroidEffectSuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

DroidEffectsModuleDataComponent::DroidEffectsModuleDataComponent() {
	active = false;
	currentEffectIndex = -1;
	setLoggingName("DroidEffectsModule");

	// Initialize configured effects
	for( int i=0; i <= 9; i++ ){
		configuredEffects.add("@pet/droid_modules:empty_slot");
		configuredDelays.add(0);
	}

}
DroidEffectsModuleDataComponent::~DroidEffectsModuleDataComponent() {

}
String DroidEffectsModuleDataComponent::getModuleName() {
	return String("effects_module");
}
void DroidEffectsModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	ManagedReference<DroidEffectsModuleTemplate*> moduleTemplate = cast<DroidEffectsModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}

	installedEffects.put( moduleTemplate->getEffectName(), moduleTemplate->getAnimation() );

}

void DroidEffectsModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {

	// Loop over all installed effects
	for(int i =0; i< installedEffects.size();i++){
		String effectName = installedEffects.elementAt(i).getKey();
		effectName = effectName.subString( effectName.indexOf(':')+1, effectName.length() );
		alm->insertAttribute( effectName, "Installed" );
	}

}

void DroidEffectsModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	info( "fillObjectMenuResponse", true);

	menuResponse->addRadialMenuItem(EFFECTS_MODULE_TOGGLE, 3, "@pet/droid_modules:toggle_effects" );
	menuResponse->addRadialMenuItem(EFFECTS_MODULE_CONFIGURE, 3, "@pet/droid_modules:effects_set_up");

	// Add slots
	for(int i=0; i <= 9; i++){
		menuResponse->addRadialMenuItemToRadialID( EFFECTS_MODULE_CONFIGURE, EFFECTS_MODULE_SLOT1+i, 3, configuredEffects.get(i));
	}

}

int DroidEffectsModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	// Handle toggle on/off
	if( selectedID == EFFECTS_MODULE_TOGGLE ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle off
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:effects_off");  // You turn off the droid's effects
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

			// Ensure we have a valid effect
			if( !nextEffect() ){
				player->sendSystemMessage("@pet/droid_modules:no_effects_program");	// The droid's effect program must have at least one active slot in order to active it.
				return 0;
			}

			// Submit effects task
			Reference<Task*> task = new DroidEffectsTask( this );
			droid->addPendingTask("droid_effects", task, 0); // 10 sec
			player->sendSystemMessage("@pet/droid_modules:effects_started");  // You turn on the droid's effects
			active = true;
		}

	}
	// Handle slot configure
	else if( EFFECTS_MODULE_SLOT1 <= selectedID && selectedID <= EFFECTS_MODULE_SLOT10 ){

		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}

		Locker dlock( droid, player );

		// Toggle effects off before allowing configuration
		if (active){
			deactivate();
			player->sendSystemMessage("@pet/droid_modules:effects_off");  // You turn off the droid's effects
		}

		int slotIndex = selectedID - EFFECTS_MODULE_SLOT1;

		// Build SUI
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::SELECT_DROID_EFFECT, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new SelectDroidEffectSuiCallback(player->getZoneServer(), this, slotIndex));
		box->setPromptText("Select the desired effect for this slot");
		box->setPromptTitle("@pet/droid_modules:effects_set_up"); // Configure Effects
		box->setOkButton(true, "@ok");
		box->setCancelButton(true, "@cancel");

		// Loop over all installed effects
		for(int i =0; i< installedEffects.size();i++){
			box->addMenuItem( installedEffects.elementAt(i).getKey() );
		}

		// Add empty slot as well to clear slot
		box->addMenuItem( "@pet/droid_modules:empty_slot" );

		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());

	}
	return 0;
}

bool DroidEffectsModuleDataComponent::nextEffect(){

	int startIdx = currentEffectIndex + 1;
	info( "nextEffect startIdx=" + String::valueOf(startIdx), true );

	// Find next valid effect
	for( int i=0; i<=9; i++){

		int nextIdx = (startIdx + i)%10;
		info( "nextEffect nextIdx=" + String::valueOf(nextIdx), true );
		if( !configuredEffects.get(nextIdx).contains("empty_slot") && configuredDelays.get(nextIdx) > 0 ){
			currentEffectIndex = nextIdx;
			info( "nextEffect currentEffectIndex=" + String::valueOf(currentEffectIndex), true );
			return true;
		}
	}

	// No valid effects configured
	return false;

}

String DroidEffectsModuleDataComponent::getCurrentAnimation(){

	if( currentEffectIndex < 0 || currentEffectIndex > 9 ){
		return "";
	}

	String effectName = configuredEffects.get(currentEffectIndex);
	info( "getCurrentAnimation=" + installedEffects.get( effectName ), true );
	return installedEffects.get( effectName );

}

int DroidEffectsModuleDataComponent::getCurrentDelay(){

	if( currentEffectIndex < 0 || currentEffectIndex > 9 ){
		return -1;
	}

	info( "getCurrentDelay=" + String::valueOf( configuredDelays.get(currentEffectIndex) ), true );
	return configuredDelays.get(currentEffectIndex);
}

void DroidEffectsModuleDataComponent::setEffect( String effectName, int delay, int slotIndex ){

	if( 0 <= slotIndex && slotIndex <= 9 ){
		configuredEffects.setElementAt( slotIndex, effectName );
		configuredDelays. setElementAt( slotIndex, delay );
		info( "setEffect configuredEffects(" + String::valueOf(slotIndex) + ")=" + effectName, true );
		info( "setEffect configuredDelays(" + String::valueOf(slotIndex) + ")=" + String::valueOf(delay), true );
	}

}

int DroidEffectsModuleDataComponent::getBatteryDrain() {

	if( active ){
		return 4;
	}

	return 0;
}

void DroidEffectsModuleDataComponent::deactivate() {

	active = false;
	currentEffectIndex = -1;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// Cancel effects task
	Task* task = droid->getPendingTask( "droid_effects" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "droid_effects" );
	}

}

String DroidEffectsModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidEffectsModuleDataComponent::onCall(){
	deactivate();
}

void DroidEffectsModuleDataComponent::onStore(){
	deactivate();
}

void DroidEffectsModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidEffectsModuleDataComponent* otherModule = cast<DroidEffectsModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	DroidComponent* droidComponent = cast<DroidComponent*>(otherModule->getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	ManagedReference<DroidEffectsModuleTemplate*> moduleTemplate = cast<DroidEffectsModuleTemplate*>(droidComponent->getObjectTemplate());
	if (moduleTemplate == NULL){
		info("Module was null");
		return;
	}

	if( !installedEffects.contains( moduleTemplate->getEffectName() ) ){
		installedEffects.put( moduleTemplate->getEffectName(), moduleTemplate->getAnimation() );
	}

}
