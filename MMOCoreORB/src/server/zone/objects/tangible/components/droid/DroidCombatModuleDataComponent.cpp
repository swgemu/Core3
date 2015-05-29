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
	int maxHam = droid->getMaximumHAM();
	int damageMin = droid->getDamageMin();
	int damageMax = droid->getDamageMax();
	float chanceHit = droid->getChanceHit();
	float attackSpeed = droid->getAttackSpeed();
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
	int maxHam = droid->getBaseHAM(0);
	int minDmg = DroidMechanics::determineMinDamage(droid->getSpecies(),rating);
	int maxDmg = DroidMechanics::determineMaxDamage(droid->getSpecies(),rating);
	float toHit = DroidMechanics::determineHit(droid->getSpecies(),maxHam);
	float speed = DroidMechanics::determineSpeed(droid->getSpecies(),maxHam);
	cast<DroidObject*>(droid)->setHitChance(toHit);
	cast<DroidObject*>(droid)->setMaxDamage(maxDmg);
	cast<DroidObject*>(droid)->setMinDamage(minDmg);
	cast<DroidObject*>(droid)->setAttackSpeed(speed);

	// load correct weapon
	if(droid->getSpecies() == DroidObject::R_SERIES) { // r-series are the ranged one users.
		String weaponTemplate = "object/weapon/ranged/droid/droid_astromech_ranged.iff";

		ManagedReference<WeaponObject*> weao = (droid->getZoneServer()->createObject(weaponTemplate.hashCode(), 1)).castTo<WeaponObject*>();
		if (weao != NULL) {
			ManagedReference<WeaponObject*> oldWeapon = droid->getSlottedObject("default_weapon").castTo<WeaponObject*>();

			if (oldWeapon != NULL && oldWeapon->isPersistent()) {
				Locker oldWeaponLocker(oldWeapon);
				oldWeapon->destroyObjectFromDatabase(true);
			}

			droid->dropSlottedObject("default_weapon");

			Locker locker(weao);

			if (!droid->transferObject(weao, 4, false)) {
				weao->destroyObjectFromDatabase(true);
			}

		}
	}
}
