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

#include "DroidDetonationModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/events/DroidDetonationTask.h"
#include "server/zone/objects/creature/CreatureObject.h"

DroidDetonationModuleDataComponent::DroidDetonationModuleDataComponent() {
	setLoggingName("DroidDetonationModule");
	rating = 0;
	moduleCount = 0;
	initialized = false;
	started = false;
	mseDroid = false;
	advanced = false;
}
DroidDetonationModuleDataComponent::~DroidDetonationModuleDataComponent() {

}
String DroidDetonationModuleDataComponent::getModuleName() {
	return String("detonation_module");
}
void DroidDetonationModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("bomb_level");
}
void DroidDetonationModuleDataComponent::initialize(CreatureObject* droid) {
	if (droid->getSpecies() == DroidObject::MSE) {
		mseDroid = true;
	}

	// ensure state on init
	started = false;
	initialized = false;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey("module_init")) {
		droidComponent->changeAttributeValue("module_init",(float)0);
	} else {
		droidComponent->addProperty("module_init",0,0,"hidden",true);
	}
}

void DroidDetonationModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	for(int i=0;i<droidComponent->getPropertyCount();i++) {
		String prop = droidComponent->getProperty(i);
	}
	if(droidComponent->hasKey("bomb_level")) {
		rating = droidComponent->getAttributeValue("bomb_level");
	}
	if(droidComponent->hasKey("module_count")) {
		moduleCount = droidComponent->getAttributeValue("module_count");
	}
	if(droidComponent->hasKey("module_init")) {
		initialized = droidComponent->getAttributeValue("module_init") == 1;
	}
	if(droidComponent->hasKey("species")) {
		species = droidComponent->getAttributeValue("species");
	}

	if(species == DroidObject::MSE) {
		mseDroid = true;
	}
}

void DroidDetonationModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	if(mseDroid) {
		int bonus = moduleCount * 10;
		alm->insertAttribute("bomb_level",rating + bonus);
	} else {
		alm->insertAttribute( "bomb_level", rating);
	}
}

void DroidDetonationModuleDataComponent::fillObjectMenuResponse(SceneObject* droidObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if( player == NULL )
		return;

	// Novie Bounty Hunter or Smuggler required to access radial
	if (player->hasSkill("combat_bountyhunter_novice") || player->hasSkill("combat_smuggler_novice")){
		menuResponse->addRadialMenuItemToRadialID(132, DETONATE_DROID, 3, "@pet/droid_modules:detonate_droid" );
	}
}
int DroidDetonationModuleDataComponent::calculateDamage(DroidObject* droid) {
	int bonus  = 0;
	if(droid->getSpecies() == DroidObject::MSE)
		bonus = moduleCount * 10;
	// generate a damage value 150 - 200 per module 175 is mid so we calc 150 + 1..50 as damage output
	return (System::random(50) + 150) * (bonus + rating);
}
void DroidDetonationModuleDataComponent::setSpecies(int i) {
	species = i;
	mseDroid = i == DroidObject::MSE;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->addProperty("species",(float)species,0,"hidden",true);
	}

}
int DroidDetonationModuleDataComponent::handleObjectMenuSelect(CreatureObject* player, byte selectedID, PetControlDevice* controller) {

	if( selectedID == DETONATE_DROID ){
		ManagedReference<DroidObject*> droid = getDroidObject();
		if( droid == NULL ){
			info( "Droid is null");
			return 0;
		}
		Locker dlock( droid, player );
		if( droid->isDead()) {
			player->sendSystemMessage("@pet/droid_modules:droid_bomb_failed");
			return 0;
		}

		// Droid must have power
		if( !droid->hasPower() ){
			droid->showFlyText("npc_reaction/flytext","low_power", 204, 0, 0);  // "*Low Power*"
			return 0;
		}
		// if the droid is already in detonation countdown we need to ignore this command
		if(droid->getPendingTask("droid_detonation") != NULL) {
			if(countdownInProgress())
				player->sendSystemMessage("@pet/droid_modules:countdown_already_started");
			else
				player->sendSystemMessage("@pet/droid_modules:detonation_warmup");
			return 0;
		}
		// droid has power and is not dead we can fire off the task
		Reference<Task*> task = new DroidDetonationTask( this,player );
		droid->addPendingTask("droid_detonation", task, 0); // queue the task for the droid to occur in 0 MS the task will handle init phase
	}
	return 0;
}

void DroidDetonationModuleDataComponent::deactivate() {

	// turn of explosion task
	ManagedReference<DroidObject*> droid = getDroidObject();
	if( droid == NULL ){
		info( "Droid is null" );
		return;
	}

	Locker dlock( droid );

	// Cancel effects task
	Task* task = droid->getPendingTask( "droid_detonaiton" );
	if( task != NULL ){
		Core::getTaskManager()->cancelTask(task);
		droid->removePendingTask( "droid_detonation" );
	}

}

String DroidDetonationModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidDetonationModuleDataComponent::onCall(){
	deactivate();
}

void DroidDetonationModuleDataComponent::onStore(){
	deactivate();
}

void DroidDetonationModuleDataComponent::addToStack(BaseDroidModuleComponent* other){
	DroidDetonationModuleDataComponent* otherModule = cast<DroidDetonationModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = rating + otherModule->rating;
	moduleCount += 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->changeAttributeValue("bomb_level",(float)rating);
		droidComponent->changeAttributeValue("module_count",(float)moduleCount);
	}

}
void DroidDetonationModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidDetonationModuleDataComponent* otherModule = cast<DroidDetonationModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = otherModule->rating;
	moduleCount = 1;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL) {
		droidComponent->addProperty("bomb_level",(float)rating,0,"exp_effectiveness");
		droidComponent->addProperty("module_count",(float)moduleCount,0,"hidden",true);
		droidComponent->addProperty("module_init",0,0,"hidden",true);
	}
}
