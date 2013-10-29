/*
Copyright (C) 2013 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
 */

#include "server/zone/objects/creature/DroidObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/templates/mobile/ConversationScreen.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/objects/creature/components/AiNPCComponent.h"

void DroidObjectImplementation::initializeTransientMembers() {
	AiAgentImplementation::initializeTransientMembers();
	aiInterfaceComponents.add(ComponentManager::instance()->getComponent<AiNPCComponent*>("AiNPCComponent"));
}

void DroidObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!player->getPlayerObject()->isPrivileged() && linkedCreature != player)
		return;

	menuResponse->addRadialMenuItem(59, 3, "@pet/pet_menu:menu_store"); //PET_STORE

	// Droid Options Submenu
	menuResponse->addRadialMenuItem(132, 3, "@pet/pet_menu:droid_options"); // SERVER_ITEM_OPTIONS
	menuResponse->addRadialMenuItemToRadialID(132, 234, 3, "@pet/pet_menu:menu_recharge" ); // PET_FEED

}

void DroidObjectImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object){

	ManagedReference<CreatureObject* > linkedCreature = this->linkedCreature.get();
	if( linkedCreature == NULL )
		return;

	msg->insertAttribute("@obj_attr_n:owner", linkedCreature->getFirstName());

	float percentPower = ((float)power/(float)MAX_POWER)*100.0;
	msg->insertAttribute("@obj_attr_n:battery_power", String::valueOf((int)percentPower) + "%");

}

int DroidObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if( player == NULL )
		return 0;

	if( linkedCreature != player )
		return 0;

	if (selectedID == 59) { // PET_STORE
		return handleStoreDroid(player);
	}
	else if (selectedID == 234 ){ // PET_FEED
		return handleRechargeDroid(player);
	}

	return 0;
}

int DroidObjectImplementation::handleRechargeDroid(CreatureObject* player){

	// Find droid battery in player inventory
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	if (inventory == NULL){
		player->sendSystemMessage("Player inventory not found");
		return 0;
	}

	ManagedReference<SceneObject*> batterySceno = NULL;
	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> sceno = inventory->getContainerObject(i);
		if( sceno->getObjectTemplate()->getFullTemplateString() == "object/tangible/droid_battery/battery.iff" ){
			batterySceno = sceno;
		}
	}

	// Battery not found
	if( batterySceno == NULL ){
		showFlyText("npc_reaction/flytext","nobattery", 204, 0, 0); // "You don't have a power storage device."
		return 0;
	}

	// Battery found
	ManagedReference<TangibleObject*> batteryTano = cast<TangibleObject*>(batterySceno.get());
	if( batteryTano == NULL ){
		player->sendSystemMessage("Error with droid battery object");
		return 0;
	}

	// Reset power to max
	power = MAX_POWER;

	// Consume battery
	batteryTano->decreaseUseCount();

	// TODO: Temporarily autofollow player
	setFollowObject( player );

	showFlyText("npc_reaction/flytext","recharged", 0, 153, 0);  // "*Recharged*"
	return 0;

}

int DroidObjectImplementation::handleStoreDroid(CreatureObject* player){
	unlock();

	try {
		ManagedReference<ControlDevice* > strongRef = controlDevice.get();

		if (strongRef != NULL)
			strongRef->storeObject(player);
	} catch (Exception& e) {

	} catch (...) {
		wlock(player);

		throw;
	}

	wlock(player);
	return 0;
}

void DroidObjectImplementation::handleLowPower(){

	// Send fly text
	showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"

	// Stop following
	setOblivious();
	return;
}
