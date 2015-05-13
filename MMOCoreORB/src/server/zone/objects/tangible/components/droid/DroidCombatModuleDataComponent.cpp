/*
 * 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

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
void DroidCombatModuleDataComponent::fillAttributeList(AttributeListMessage* alm, CreatureObject* creature) {
	// convert module rating to actual rating
	alm->insertAttribute( "cmbt_module", rating);
	// Should insert Base Stuff for hit/min/max/speed values
	ManagedReference<DroidObject*>  droid = getDroidObject();
	if( droid == NULL){
		return;
	}
	// lets make a pcd
	int maxHam = droid->getMaxHAM(0);
	int damageMin = droid->getDamageMin();
	int damageMax = droid->getDamageMax();
	float chanceHit = droid->getChanceHit();
	float attackSpeed = droid->calculateAttackSpeed(0);
	StringBuffer attdisplayValue;
	attdisplayValue << Math::getPrecision(attackSpeed, 2);
	StringBuffer hitdisplayValue;
	hitdisplayValue << Math::getPrecision(chanceHit, 2);
	alm->insertAttribute("creature_attack", attdisplayValue);
	alm->insertAttribute("creature_tohit", hitdisplayValue);
	alm->insertAttribute("creature_damage", String::valueOf(damageMin) + " - " + String::valueOf(damageMax));
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
	cast<DroidObject*>(droid)->setMaxDamage(maxDmg);
	cast<DroidObject*>(droid)->setMinDamage(maxDmg);

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

		if (!droid->transferObject(weao, 4, false)) {
			weao->destroyObjectFromDatabase(true);
		}
	}

}
