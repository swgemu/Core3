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

#include "DroidMedicalModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

DroidMedicalModuleDataComponent::DroidMedicalModuleDataComponent() {
	setLoggingName("DroidMedicalModule");
	rating = 0;
}
DroidMedicalModuleDataComponent::~DroidMedicalModuleDataComponent() {

}
String DroidMedicalModuleDataComponent::getModuleName() {
	return String("medical_module");
}
void DroidMedicalModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "medical_module")) {
		rating = droidComponent->getAttributeValue( "medical_module");
	}
}
void DroidMedicalModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("medical_module");
}
int DroidMedicalModuleDataComponent::getMedicalRating() {
	switch(rating) {
		case 1:
		case 2:
			return 55;
		case 3:
		case 4:
			return 65;
		case 5:
		case 6:
			return 75;
		case 7:
		case 8:
			return 85;
		case 9:
		case 10:
			return 100;
	}
	return 110;
}
void DroidMedicalModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "medical_module", getMedicalRating() );
}
String DroidMedicalModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidMedicalModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidMedicalModuleDataComponent* otherModule = cast<DroidMedicalModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = rating + otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->changeAttributeValue("medical_module",(float)rating);
}
void DroidMedicalModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidMedicalModuleDataComponent* otherModule = cast<DroidMedicalModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->addProperty("medical_module",(float)rating,0,"exp_effectiveness");
}
void DroidMedicalModuleDataComponent::onCall() {
	// no op
}
void DroidMedicalModuleDataComponent::onStore() {
	// no op on store
}
void DroidMedicalModuleDataComponent::loadSkillMods(CreatureObject* player) {
	// add the rating to the player as a private medical center for right now we ignore the part about not usable in a static cantina we will handle that in the injury treatment task
	// only add this is the payer didnt have it already.
	if(player->getSkillModOfType("private_medical_rating",SkillModManager::DROID)  == 0) {
		player->addSkillMod(SkillModManager::DROID,"private_medical_rating",getMedicalRating(),true);
	}
}
void DroidMedicalModuleDataComponent::unloadSkillMods(CreatureObject* player) {
	player->removeSkillMod(SkillModManager::DROID,"private_medical_rating",true);
}

