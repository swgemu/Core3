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

#include "DroidArmorModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"

DroidArmorModuleDataComponent::DroidArmorModuleDataComponent() {
	armorModule = 0;
	setLoggingName("DroidArmorModule");
}

DroidArmorModuleDataComponent::~DroidArmorModuleDataComponent() {

}

String DroidArmorModuleDataComponent::getModuleName() {
	return String("armor_module");
}

void DroidArmorModuleDataComponent::initializeTransientMembers() {

	// Pull module stat from parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}

	if( droidComponent->hasKey( "armor_module") ){
		armorModule = droidComponent->getAttributeValue( "armor_module");
	}

}

void DroidArmorModuleDataComponent::initialize(CreatureObject* creature) {
	// Change droid resist and armor stat

	DroidObject* droid = cast<DroidObject*>(creature);
	if( droid == NULL )
		return;

	int level = armorModule;
	unsigned int armor = 0;
	float resist = -1;

	// Capped at 6
	if( level > 6 )
		level = 6;

	// Set armor type
	if( level == 0 ){
		armor = 0; // NO ARMOR
	}
	else if( level <= 3 ){
		armor = 1; // LIGHT ARMOR
	}
	else if( level <= 6 ){
		armor = 2; // MEDIUM ARMOR
	}

	// Set damage resistance
	if( level == 1 || level == 4 ){
		resist = 15;
	}
	else if( level == 2 || level == 5 ){
		resist = 25;
	}
	else if( level == 3 || level == 6 ){
		resist = 40;
	}

	droid->setArmor( armor );
	droid->setResists( resist );

}

void DroidArmorModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// Armor/resists filled from AiAgent, but add total module level  here for deeds/components
	alm->insertAttribute( "armor_module", armorModule );
}

int DroidArmorModuleDataComponent::getBatteryDrain() {
	return 0;
}

String DroidArmorModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}

void DroidArmorModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	armorModule = values->getCurrentValue("armor_module");
}

void DroidArmorModuleDataComponent::addToStack(BaseDroidModuleComponent* other){

	DroidArmorModuleDataComponent* otherModule = cast<DroidArmorModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	armorModule = armorModule + otherModule->armorModule;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	// Attribute should have already been created in copy method
	if( !droidComponent->changeAttributeValue( "armor_module", armorModule) ){
		info( "addToStack updateAttributeValue failed");
		return;
	}

}

void DroidArmorModuleDataComponent::copy(BaseDroidModuleComponent* other){

	DroidArmorModuleDataComponent* otherModule = cast<DroidArmorModuleDataComponent*>(other);
	if( otherModule == NULL )
		return;

	armorModule = otherModule->armorModule;

	// Save stat in parent sceno
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL)
		return;

	droidComponent->addProperty("armor_module", armorModule, 0, "exp_effectiveness");

}
