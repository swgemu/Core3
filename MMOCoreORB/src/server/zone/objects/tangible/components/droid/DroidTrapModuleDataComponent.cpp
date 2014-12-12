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

#include "DroidTrapModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/events/DroidTrapTask.h"
#include "server/zone/templates/tangible/TrapTemplate.h"

DroidTrapModuleDataComponent::DroidTrapModuleDataComponent() {
	setLoggingName("DroidTrapModule");
	trapBonus = 0;
	loaded = 0;
	modules = 1;
}
DroidTrapModuleDataComponent::~DroidTrapModuleDataComponent() {

}
String DroidTrapModuleDataComponent::getModuleName() {
	return String("trap_module");
}
void DroidTrapModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "trap_bonus")) {
		trapBonus = droidComponent->getAttributeValue( "trap_bonus");
	}
	if(droidComponent->hasKey( "module_count")) {
		modules = droidComponent->getAttributeValue( "module_count");
	}
	// ned to determine how to store the modules
}
void DroidTrapModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	trapBonus = values->getCurrentValue("trap_bonus");
}
void DroidTrapModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "trap_bonus", trapBonus);
	alm->insertAttribute("droid_trap_type", "installed"); // TODO mark the current Trap Type based on loaded
	alm->insertAttribute("max_trap_load",loaded +"/"+ (modules * 10));
}
String DroidTrapModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidTrapModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidTrapModuleDataComponent* otherModule = cast<DroidTrapModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	trapBonus = trapBonus + otherModule->trapBonus;
	modules += 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->changeAttributeValue("trap_bonus",(float)trapBonus);
		droidComponent->changeAttributeValue("module_count",(float)modules);
	}
}
void DroidTrapModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidTrapModuleDataComponent* otherModule = cast<DroidTrapModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	trapBonus = otherModule->trapBonus;
	modules = 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL){
		droidComponent->addProperty("trap_bonus",(float)trapBonus,0,"exp_effectiveness");
		droidComponent->addProperty("module_count",(float)modules,0,"hidden",true);
	}
}
void DroidTrapModuleDataComponent::onCall() {
	// recalculate the rate
	countUses();
}
bool DroidTrapModuleDataComponent::compatibleTrap(uint32 type) {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return false;
	}
	DroidObject* droid = getDroidObject();
	if (droid == NULL) {
		return false;
	}
	Locker dlock(droid);
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if(craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		if(satchel == NULL) {
			System::out << "satch null for compa call\n";
			return NULL;
		}
		if (satchel->getContainerObjectsSize() >0) {
			SceneObject* item = satchel->getContainerObject(0);
			if (item != NULL){
				uint32 crc = item->getServerObjectCRC();
				return crc == type;
			}
		}
	}
	return false;
}
void DroidTrapModuleDataComponent::countUses() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	DroidObject* droid = getDroidObject();
	if (droid == NULL) {
		return ;
	}
	Locker dlock(droid);
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if(craftingComponents != NULL) {
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		if (satchel == NULL) {
			return;
		}
		loaded = 0;
		for (int i = 0; i < satchel->getContainerObjectsSize(); ++i) {
			SceneObject* item = satchel->getContainerObject(i);
			if (!item->isTangibleObject())
				continue;

			TangibleObject* tano = cast<TangibleObject*>( item);
			loaded = tano->getUseCount();
		}
	}
}

void DroidTrapModuleDataComponent::onStore() {
	// no-op
	countUses();
}
/**
 * Add Droid sub-radial options, need to be a top level radial not submenu
 */
void DroidTrapModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player != NULL && player->hasSkill("science_medic_ability_04")) {
		menuResponse->addRadialMenuItem(TRAP_MODULE_CONTROLS, 3, "@pet/droid_modules:throw_trap_options" );
		menuResponse->addRadialMenuItemToRadialID(TRAP_MODULE_CONTROLS, TRAP_MODULE_TRAIN, 3, "@pet/droid_modules:train_throw_one" );
		menuResponse->addRadialMenuItemToRadialID(TRAP_MODULE_CONTROLS, TRAP_MODULE_CLEAR, 3, "@pet/droid_modules:clear_trap" );
	}
}
void DroidTrapModuleDataComponent::initialize(CreatureObject* droid) {
	// grab the crafted components in this module and remove then
	// then change capacity to the new capacity so we store the stims directly in the component.
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	droidComponent->dropSlottedObject("crafted_components");
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if(craftingComponents == NULL) {
		// create the satchel and container as it would not be present as this object doesnt use components.
		ManagedReference<SceneObject*> craftingComponentsSatchel = NULL;
		String craftingComponentsPath = "object/tangible/crafting/crafting_components_container.iff";
		craftingComponents = droidComponent->getZoneServer()->createObject(craftingComponentsPath.hashCode(), 1);
		craftingComponents->removeAllContainerObjects();
		craftingComponents->setSendToClient(false);
		droidComponent->transferObject(craftingComponents, 4, false);
		craftingComponents->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDefaultAllowPermission(0);
		craftingComponents->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerDenyPermission("admin", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponents->setContainerAllowPermission("owner", 0);
		craftingComponents->setContainerAllowPermission("admin", 0);
		craftingComponents->setContainerInheritPermissionsFromParent(false);

		String craftingComponentsSatchelPath = "object/tangible/hopper/crafting_station_hopper/crafting_station_ingredient_hopper_large.iff";
		craftingComponentsSatchel = droidComponent->getZoneServer()->createObject(craftingComponentsSatchelPath.hashCode(), 1);
		craftingComponentsSatchel->setContainerVolumeLimit(1);
		craftingComponentsSatchel->setContainerInheritPermissionsFromParent(false);
		craftingComponentsSatchel->setContainerDefaultDenyPermission(ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerDefaultAllowPermission(0);
		craftingComponentsSatchel->setContainerAllowPermission("admin", ContainerPermissions::OPEN);
		craftingComponentsSatchel->setContainerDenyPermission("admin", ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->setContainerAllowPermission("owner", 0);
		craftingComponentsSatchel->setContainerDenyPermission("owner", ContainerPermissions::OPEN + ContainerPermissions::MOVEIN + ContainerPermissions::MOVEOUT + ContainerPermissions::MOVECONTAINER);
		craftingComponentsSatchel->sendTo(droid, true);
		craftingComponents->transferObject(craftingComponentsSatchel, -1, false);
	}
}
int DroidTrapModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	ManagedReference<DroidObject*> droid = getDroidObject();
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if( droid == NULL || droidComponent == NULL){
		return 0;
	}
	if( droid->isDead() || droid->isIncapacitated() || player->isDead()) {
		return 0;
	}
	if( !droid->hasPower() ){
		droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
		return 0;
	}

	if( selectedID == TRAP_MODULE_TRAIN ){
		if( controller == NULL )
			return 0;

		controller->setTrainingCommand( PetManager::THROWTRAP );
		return 0;
	}

	if( selectedID == TRAP_MODULE_CLEAR ){
	}
	return 0;
}
void DroidTrapModuleDataComponent::handlePetCommand(String cmd, CreatureObject* speaker){

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

	if( petManager->isTrainedCommand( pcd, PetManager::THROWTRAP, cmd ) ){
		petManager->enqueuePetCommand(speaker, droid, String("petThrow").toLowerCase().hashCode(), "");
	}
}


void DroidTrapModuleDataComponent::handleInsertTrap(CreatureObject* player, TangibleObject* trap) {
	// we need to send the invlid stimpack message just wher eis a good question
	countUses();
	if (player != NULL && !player->hasSkill("outdoors_scout_novice")) {
		player->sendSystemMessage("@pet/droid_modules:insufficient_skill");
		return;
	}
	ManagedReference<DroidObject*> droid = getDroidObject();
	if (droid == NULL) {
		return;
	}
	if (trap == NULL) {
		return;
	}
	if(droid->getLinkedCreature().get() != player) {
		return;
	}
	// we have the player and the stim to add to ourselves.
	// code should goes as follow, count total use of all stims, then deduct amount form capacity
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	ManagedReference<SceneObject*> craftingComponents = droidComponent->getSlottedObject("crafted_components");
	if (craftingComponents != NULL){
		SceneObject* satchel = craftingComponents->getContainerObject(0);
		if(satchel == NULL) {
			return;
		}
		if (satchel->getContainerObjectsSize() >0) {
			SceneObject* item = satchel->getContainerObject(0);
			if (item != NULL){
				if (item->getServerObjectCRC() == trap->getServerObjectCRC()) {
					TangibleObject* tano = cast<TangibleObject*>(item);
					// take charges if we can
					int allowed = (modules * 10) - loaded;
					if (allowed <= 0) {
						player->sendSystemMessage("@pet/droid_modules:trap_matrix_full");
					} else {
						if (allowed > trap->getUseCount()) {
							tano->setUseCount(tano->getUseCount() + trap->getUseCount(),true);
							trap->setUseCount(0,true);
						} else {
							tano->setUseCount(tano->getUseCount() + allowed,true);
							trap->setUseCount(trap->getUseCount() - allowed,true);
							player->sendSystemMessage("@pet/droid_modules:trap_max_reached");
						}
					}
				} else {
					player->sendSystemMessage("@pet/droid_modules:already_loaded");
				}
			} else {
				// new trap
				if (trap->isTrapObject()) {
					SharedObjectTemplate* templateData =TemplateManager::instance()->getTemplate(trap->getServerObjectCRC());
					if (templateData == NULL) {
						error("No template for: " + String::valueOf(trap->getServerObjectCRC()));
						return;
					}
					TrapTemplate* trapData = cast<TrapTemplate*> (templateData);
					if (trapData == NULL) {
						error("No TrapTemplate for: " + String::valueOf(trap->getServerObjectCRC()));
						return;
					}
					int trappingSkill = player->getSkillMod("trapping");
					if(trappingSkill < 1) {
						player->sendSystemMessage("@pet/droid_modules:insufficient_skill");
						return;
					}
					/// Skill too low check
					if(trappingSkill < trapData->getSkillRequired()) {
						player->sendSystemMessage("@pet/droid_modules:insufficient_skill");
						return;
					}
					trap->destroyObjectFromWorld(true);
					satchel->transferObject(trap,-1,true);
					satchel->broadcastObject(trap,true);
					trap->sendTo(player,true);
					droid->sendTo(player,true);
					StringIdChatParameter msg;
					msg.setStringId("@pet/droid_modules:trap_module_initialize");
					msg.setDI(trap->getUseCount());
					msg.setTU(trap->getObjectName()->toString());
					player->sendSystemMessage(msg);
				}
			}
		}

	}
}
int DroidTrapModuleDataComponent::getBatteryDrain() {
	return 0;
}
