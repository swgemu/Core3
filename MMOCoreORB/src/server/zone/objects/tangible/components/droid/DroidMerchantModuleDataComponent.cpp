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

#include "DroidMerchantModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/events/DroidMerchantBarkerTask.h"
#include "server/zone/objects/player/sui/callbacks/SelectWaypointSuiCallback.h"

DroidMerchantModuleDataComponent::DroidMerchantModuleDataComponent() {
	active = false;
	waitingOnMessage = false;
	message = "";
}
DroidMerchantModuleDataComponent::~DroidMerchantModuleDataComponent() {

}
String DroidMerchantModuleDataComponent::getModuleName() {
	return String("merchant_barker");
}
void DroidMerchantModuleDataComponent::initializeTransientMembers() {
	// no Op
}

void DroidMerchantModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	alm->insertAttribute( "merchant_barker", "Installed" );
}

void DroidMerchantModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if( player == NULL )
		return;
	// Add Get waypoint Radial, not under droid options
	//if(player != getDroidObject()->getLinkedCreature()) was this shown to the owner?
	menuResponse->addRadialMenuItem(70,3,"@pet/droid_modules:merchant_barker"); // Get Waypoint
	// Novice Musician or Novice Dancer required to utilize this module
	if (player->hasSkill("crafting_merchant_advertising_04")){
		menuResponse->addRadialMenuItemToRadialID(132,BARKER_RECORD_MESSAGE,3, "@pet/droid_modules:record_message"); // Record
		menuResponse->addRadialMenuItemToRadialID(132,BARKER_STORE_WAYPOINT,3, "@pet/droid_modules:store_waypoint"); // Store a Way point
		menuResponse->addRadialMenuItemToRadialID(132,BARKER_TOGGLE,3, "@pet/droid_modules:barker_on_off"); // Toggle
	}

}
void DroidMerchantModuleDataComponent::setWaypoint(ManagedReference<WaypointObject*> wp) {
	waypoint = ( getParent()->getZoneServer()->createObject(0xc456e788, 0)).castTo<WaypointObject*>();
	waypoint->setPlanetCRC(wp->getPlanetCRC());
	waypoint->setPosition(wp->getPositionX(), wp->getPositionZ(), wp->getPositionY());
	waypoint->setActive(true);
	waypoint->setColor(WaypointObject::SPECIALTYPE_FIND);
	waypoint->setCustomObjectName(wp->getDisplayedName(),false);
}
int DroidMerchantModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	if( selectedID == 70 ){
		// handle the waypoint
		if(waypoint == NULL) {
			player->sendSystemMessage("@pet/droid_modules:no_waypoint");
			return 0;
		}
		// create a way point and give to player
		ManagedReference<WaypointObject*> tway = ( player->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();
		tway->setPlanetCRC(waypoint->getPlanetCRC());
		tway->setPosition(waypoint->getPositionX(), waypoint->getPositionZ(), waypoint->getPositionY());
		tway->setActive(true);
		tway->setCustomObjectName(waypoint->getDisplayedName(),true);
		tway->setColor(WaypointObject::SPECIALTYPE_FIND);
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ghost->addWaypoint(tway,true,true);
		player->sendSystemMessage("@pet/droid_modules:waypoint_sent");
	}
	else if (selectedID == BARKER_RECORD_MESSAGE) {
		// record the emssage
		if(waitingOnMessage == false) {
			player->sendSystemMessage("@pet/droid_modules:recording_message_on");
			waitingOnMessage = true;
		} else {
			player->sendSystemMessage("@pet/droid_modules:recording_message_off");
			waitingOnMessage = false;
		}
	}
	else if( selectedID == BARKER_TOGGLE ){
		// handle toggle
		if(active) {
			player->sendSystemMessage("@pet/droid_modules:barking_off");
			deactivate();
		} else {
			ManagedReference<DroidObject*> droid = getDroidObject();
			if( droid == NULL ){
				info( "Droid is null");
				return 0;
			}

			Locker dlock( droid, player );

			if( droid->isDead() || droid->isIncapacitated() )
				return 0;

			// Droid must have power
			if( !droid->hasPower() ){
				droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
				return 0;
			}

			// Ensure we don't accidentally have another task outstanding
			deactivate();
			if(message.length() == 0) {
				player->sendSystemMessage("@pet/droid_modules:no_message_to_bark");
				return 0;
			}
			// Submit barker task
			Reference<Task*> task = new DroidMerchantBarkerTask( this );
			droid->addPendingTask("barking", task, 10000); // 10 sec
			player->sendSystemMessage("@pet/droid_modules:barking_on");
			active = true;
		}
	}
	else if (selectedID == BARKER_STORE_WAYPOINT) {
		// Handle the waypoint input
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		WaypointList* waypoints = ghost->getWaypointList();
		if(waypoints->size() == 0) {
			player->sendSystemMessage("@pet/droid_modules:no_waypoints_in_datapad");
			return 0;
		}
		ManagedReference<SuiListBox*> box = new SuiListBox(player, SuiWindowType::SELECT_MERCHANT_WAYPOINT, SuiListBox::HANDLETWOBUTTON);
		box->setCallback(new SelectWaypointSuiCallback(player->getZoneServer(), this));
		box->setPromptText("@pet/droid_modules:barker_message_body");
		box->setPromptTitle("@pet/droid_modules:barker_message_sub"); // Configure Effects
		box->setOkButton(true, "@ok");
		box->setCancelButton(true, "@cancel");
		for(int i=0;i<waypoints->size();i++) {
			ManagedReference<WaypointObject*> way = waypoints->getValueAt(i);
			box->addMenuItem(way->getDisplayedName(),way->getObjectID());
		}
		ManagedReference<DroidObject*> droid = getDroidObject();
		box->setUsingObject(droid);
		player->getPlayerObject()->addSuiBox(box);
		player->sendMessage(box->generateMessage());
	}
	return 0;
}


int DroidMerchantModuleDataComponent::getBatteryDrain() {

	if( active ){
		return 4;
	}

	return 0;
}

void DroidMerchantModuleDataComponent::deactivate() {

	active = false;

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// Cancel effects task
	Task* task = droid->getPendingTask( "barking" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "barking" );
	}

}

String DroidMerchantModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidMerchantModuleDataComponent::onCall(){
	message = "";
	message = "";
	active = false;
	waitingOnMessage = false;
	if(waypoint != NULL) {
		waypoint->destroyObjectFromWorld(true);
		waypoint->destroyObjectFromDatabase(true);
		waypoint = NULL;
	}
	deactivate();
}

void DroidMerchantModuleDataComponent::onStore(){
	message = "";
	active = false;
	waitingOnMessage = false;
	if(waypoint != NULL) {
		waypoint->destroyObjectFromWorld(true);
		waypoint->destroyObjectFromDatabase(true);
		waypoint = NULL;
	}
	deactivate();
}
void DroidMerchantModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){
	if(waitingOnMessage) { // only check if we are recording.
		if(cmd.length() > 128) {
			speaker->sendSystemMessage("@pet/droid_modules:message_too_long");
		} else {
			message = cmd;
			waitingOnMessage = false;
			speaker->sendSystemMessage("@pet/droid_modules:message_saved");
		}
	}
}
