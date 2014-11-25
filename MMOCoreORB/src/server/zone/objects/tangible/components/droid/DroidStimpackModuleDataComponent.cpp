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

#include "DroidStimpackModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

DroidStimpackModuleDataComponent::DroidStimpackModuleDataComponent() {
	setLoggingName("DroidStimpackModule");
	speed = 0;
	capacity = 0;
	rate = 0;
}
DroidStimpackModuleDataComponent::~DroidStimpackModuleDataComponent() {

}
String DroidStimpackModuleDataComponent::getModuleName() {
	return String("stimpack_module");
}
void DroidStimpackModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "stimpack_caoacity")) {
		capacity = droidComponent->getAttributeValue( "stimpack_caoacity");
	}
	if (droidComponent->hasKey("stimpack_speed")) {
		speed = droidComponent->getAttributeValue("stimpack_speed");
	}
}
void DroidStimpackModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	capacity = values->getCurrentValue("stimpack_capacity");
	speed = values->getCurrentValue("stimpack_speed");
}
void DroidStimpackModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "stimpack_capacity", capacity);
	alm->insertAttribute( "stimpack_speed", speed);
}
String DroidStimpackModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidStimpackModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidStimpackModuleDataComponent* otherModule = cast<DroidStimpackModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	speed = speed + otherModule->speed;
	capacity = capacity + otherModule->capacity;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->changeAttributeValue("stimpack_capacity",(float)capacity);
		droidComponent->changeAttributeValue("stimpack_speed",(float)speed);
	}
}
void DroidStimpackModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidStimpackModuleDataComponent* otherModule = cast<DroidStimpackModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	speed = speed + otherModule->speed;
	capacity = capacity + otherModule->capacity;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->addProperty("stimpack_speed",(float)speed,0,"exp_effectiveness");
		droidComponent->addProperty("stimpack_capacity",(float)capacity,0,"exp_durability");
	}
}
void DroidStimpackModuleDataComponent::onCall() {
	// no op
	if (speed == 0) {
		rate = 60000;
	} else {
		rate = round((float)60 * ((float)1 / (float)speed)) * 1000;
	}
}
void DroidStimpackModuleDataComponent::onStore() {
	// no op on store
}
void DroidStimpackModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	// Add to Droid Options subradial from PetMenuComponent
	menuResponse->addRadialMenuItemToRadialID(132, REQUEST_STIMPACK, 3, "@pet/droid_modules:request_stimpack" );
	menuResponse->addRadialMenuItemToRadialID(132, LOAD_STIMPACK, 3, "@pet/droid_modules:load_stimpack" );
}
void DroidStimpackModuleDataComponent::initialize(CreatureObject* droid) {
	// grab the crafted components in this module and remove then
	// then change capacity to the new capacity so we store the stims directly in the component.
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	// get the inventory of the component.
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if(craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		// remove all items form satchel and add int he new items
		Vector<ManagedReference<SceneObject*> > toRemove;
		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
			if (sceno != NULL) {
				toRemove.add(sceno);
			}
		}
		satchel->removeAllContainerObjects();
		for(int i=0;i<toRemove.size();i++) {
			toRemove.get(i)->destroyObjectFromWorld(true);
		}
		// satchel is empty and new volume limit has been set.
		satchel->setContainerVolumeLimit(capacity);
	}
}
int DroidStimpackModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	ManagedReference<DroidObject*> droid = getDroidObject();
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if( droid == NULL ){
		player->sendSystemMessage("@pet/droid_modules:stimpack_error");
		return 0;
	}
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	ManagedReference<StimPack*> stim = NULL;
	if(craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
			ManagedReference<SceneObject*> sceno = satchel->getContainerObject(i);
			ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceno.get());

			if (tano != NULL ) {
				// is a stimpack
				if (tano->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( tano.get());
					if (pharma->isStimPack() && !pharma->isPetStimPack() && !pharma->isDroidRepairKit()) {
						stim = cast<StimPack*>(pharma);
					}
				}
			}
		}
	}

	if( selectedID == LOAD_STIMPACK ){
		Locker locker(player);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if (inventory == NULL) {
			player->sendSystemMessage("@pet/droid_modules:no_stimpacks");
			return 0;
		}
		for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
			SceneObject* item = inventory->getContainerObject(i);

			if (!item->isTangibleObject())
				continue;

			TangibleObject* tano = cast<TangibleObject*>( item);

			if (tano->isPharmaceuticalObject()) {
				PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( tano);
				if (pharma->isStimPack()) {
					if (craftingComponents != NULL) {
						SceneObject* satchel = craftingComponents->getContainerObject(0);
						bool didit = satchel->transferObject(pharma,-1,true);
						if(!didit) {
							player->sendSystemMessage("@pet/droid_modules:stimpack_capacity_full");
						} else {
							player->sendSystemMessage("@pet/droid_modules:stimpack_loaded");
						}
					}
				}
			}
		}
	}
	if( selectedID == REQUEST_STIMPACK ){
		// we need to check cooldown on droid
		if (droid->getCooldownTimerMap()->isPast("RequestStimpack")) {
			if (stim == NULL) {
				player->sendSystemMessage("@pet/droid_modules:stimpack_supply_empty");
				return 0;
			}
			// do we have the module correctly.
			if (droidComponent == NULL) {
				// send stim pack error message
				player->sendSystemMessage("@pet/droid_modules:stimpack_error");
				return 0;
			}
			// is the player damaged
			if (!player->hasDamage(CreatureAttribute::HEALTH) && !player->hasDamage(CreatureAttribute::ACTION)) {
				player->sendSystemMessage("@pet/droid_modules:stimpack_no_damage");
				return 0;
			}
			// is the player in range
			if (!player->isInRange(droid,20)){
				// 20 meter range same as max possible range stim
				player->sendSystemMessage("@pet/droid_modules:stimpack_too_far_away");
				return 0;
			}
			ManagedReference<GroupObject*> group = player->getGroup();
			bool groupMember = false;
			if (group != NULL) {
				Locker locker(group);
				GroupObject* g;
				for(int i=0;i<g->getGroupSize();i++) {
					ManagedReference<SceneObject*> member = group->getGroupMember(i);
					if(member->isPlayerObject()) {
						ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());
						if (memberPlayer == player) {
							groupMember = true;
						}
					}
				}
			}
			// is the player in the group or owner
			if( player != droid->getLinkedCreature().get() || !groupMember ) {
				player->sendSystemMessage("@pet/droid_modules:stimpack_cant_use_droid");
				return 0;
			}
			// ok lets heal
			// use the stim pack
			player->playEffect("clienteffect/healing_healdamage.cef", "");
			droid->doAnimation("heal_other");
			uint32 stimPower = stim->calculatePower(droid, player);
			uint32 healthHealed = player->healDamage(droid, CreatureAttribute::HEALTH, stimPower);
			uint32 actionHealed = player->healDamage(droid, CreatureAttribute::ACTION, stimPower, true, false);
			stim->decreaseUseCount();
			droid->getCooldownTimerMap()->updateToCurrentAndAddMili("RequestStimpack",rate);
			// send heal message
			StringBuffer msgPlayer, msgTarget, msgBody, msgTail;
			if (healthHealed > 0 && actionHealed > 0) {
				msgBody << healthHealed << " health and " << actionHealed << " action";
			} else if (healthHealed > 0) {
				msgBody << healthHealed << " health";
			} else if (actionHealed > 0) {
				msgBody << actionHealed << " action";
			}
			msgTail << " damage.";
			msgTarget << controller->getCustomObjectName().toString() << " heals you for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgTarget.toString());
		} else {
			player->sendSystemMessage("@pet/droid_modules:stimpack_not_ready");
			return 0;
		}
	}
	return 0;
}
int DroidStimpackModuleDataComponent::getBatteryDrain() {
	return 2;
}
void DroidStimpackModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL )
		return;

	ManagedReference<PetControlDevice*> pcd = droid->getControlDevice().get().castTo<PetControlDevice*>();
	if( pcd == NULL )
		return;
	// will need to handle this later
}
