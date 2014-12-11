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

#include "DroidCombatModuleDataComponent.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/component/droid/DroidComponent.h"
#include "server/zone/managers/crafting/labratories/DroidMechanics.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

DroidCombatModuleDataComponent::DroidCombatModuleDataComponent() {
	setLoggingName("DroidCombatModule");
	rating = 0;
}
DroidCombatModuleDataComponent::~DroidCombatModuleDataComponent() {

}
String DroidCombatModuleDataComponent::getModuleName() {
	return String("combat_module");
}
void DroidCombatModuleDataComponent::initializeTransientMembers() {
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent == NULL) {
		info("droidComponent was null");
		return;
	}
	if(droidComponent->hasKey( "cmbt_module")) {
		rating = droidComponent->getAttributeValue( "cmbt_module");
	}
}
void DroidCombatModuleDataComponent::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	rating = values->getCurrentValue("cmbt_module");
}
void DroidCombatModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* droid) {
	// convert module rating to actual rating
	alm->insertAttribute( "cmbt_module", rating);
}
String DroidCombatModuleDataComponent::toString(){
	return BaseDroidModuleComponent::toString();
}
void DroidCombatModuleDataComponent::addToStack(BaseDroidModuleComponent* other) {
	DroidCombatModuleDataComponent* otherModule = cast<DroidCombatModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = rating + otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->changeAttributeValue("cmbt_module",(float)rating);
}
void DroidCombatModuleDataComponent::copy(BaseDroidModuleComponent* other) {
	DroidCombatModuleDataComponent* otherModule = cast<DroidCombatModuleDataComponent*>(other);
	if(otherModule == NULL)
		return;
	rating = otherModule->rating;
	DroidComponent* droidComponent = cast<DroidComponent*>(getParent());
	if (droidComponent != NULL)
		droidComponent->addProperty("cmbt_module",(float)rating,0,"exp_effectiveness");
}
void DroidCombatModuleDataComponent::initialize(CreatureObject* droid) {
	// create the weapons and set them on the droid
	// also change the ham values
	int maxHam = droid->getMaxHAM(0);
	int minDmg = DroidMechanics::determineMinDamage(droid->getSpecies(),rating);
	int maxDmg = DroidMechanics::determineMaxDamage(droid->getSpecies(),rating);
	float toHit = DroidMechanics::determineHit(droid->getSpecies(),maxHam);
	float speed = DroidMechanics::determineSpeed(droid->getSpecies(),maxHam);
	cast<DroidObject*>(droid)->setHitChance(toHit);
	// load correct weapon
	String weaponTemplate = "object/weapon/creature/creature_default_weapon.iff";
	if(droid->getSpecies() == DroidObject::R_SERIES) { // r-series are the ranged one users.
		weaponTemplate = "object/weapon/ranged/droid/droid_astromech_ranged.iff";
	}
	ManagedReference<WeaponObject*> weao = (droid->getZoneServer()->createObject(weaponTemplate.hashCode(), 1)).castTo<WeaponObject*>();
	if (weao != NULL) {
		weao->setMinDamage(minDmg);
		weao->setMaxDamage(maxDmg);
		weao->setAttackSpeed(speed);

		WeaponObject* oldWeapon = droid->getSlottedObject("default_weapon").castTo<WeaponObject*>();

		if (oldWeapon != NULL && oldWeapon->isPersistent()) {
			oldWeapon->destroyObjectFromDatabase(true);
		}

		droid->dropSlottedObject("default_weapon");

		droid->transferObject(weao, 4, false);
	}

}
