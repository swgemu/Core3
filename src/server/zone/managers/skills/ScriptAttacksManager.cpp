/*
Copyright (C) 2007 <SWGEmu>

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

#include "ScriptAttacksManager.h"

#include "../../objects/tangible/weapons/Weapon.h"
#include "../../objects/tangible/weapons/JediWeapon.h"

#include "../../objects/creature/skills/Skill.h"
#include "../../objects/creature/skills/skills.h"

#include "../../ZoneProcessServerImplementation.h"
#include "SkillList.h"

SkillList* ScriptAttacksManager::CombatActions = NULL;
ZoneProcessServerImplementation* ScriptAttacksManager::server = NULL;

ScriptAttacksManager::ScriptAttacksManager(ZoneProcessServerImplementation* serv) {
	server = serv;

	init();

	registerFunctions();
	registerGlobals();
}

void ScriptAttacksManager::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunSkillsFile", RunSkillsFile);

	//AddSkills
	lua_register(getLuaState(), "AddRandomPoolAttackTargetSkill", AddRandomPoolAttackTargetSkill);
	lua_register(getLuaState(), "AddDirectPoolAttackTargetSkill", AddDirectPoolAttackTargetSkill);
	lua_register(getLuaState(), "AddForcePowersPoolAttackTargetSkill", AddForcePowersPoolAttackTargetSkill);
	//lua_register(getLuaState(), "AddWeaponlessDotPoolAttackTargetSkill", AddWeaponlessDotPoolAttackSkill);
	lua_register(getLuaState(), "AddForceHealSelfSkill", AddForceHealSelfSkill);
	lua_register(getLuaState(), "AddHealSelfSkill", AddHealSelfSkill);
	lua_register(getLuaState(), "AddHealTargetSkill", AddHealTargetSkill);
	lua_register(getLuaState(), "AddHealEnhanceTargetSkill", AddHealEnhanceTargetSkill);
	lua_register(getLuaState(), "AddHealDamageTargetSkill", AddHealDamageTargetSkill);
	lua_register(getLuaState(), "AddHealStateTargetSkill", AddHealStateTargetSkill);
	lua_register(getLuaState(), "AddHealWoundTargetSkill", AddHealWoundTargetSkill);
	lua_register(getLuaState(), "AddCureTargetSkill", AddCureTargetSkill);
	lua_register(getLuaState(), "AddReviveTargetSkill", AddReviveTargetSkill);
	lua_register(getLuaState(), "AddFirstAidTargetSkill", AddFirstAidTargetSkill);
	lua_register(getLuaState(), "AddTendHealTargetSkill", AddTendHealTargetSkill);
	lua_register(getLuaState(), "AddQuickHealTargetSkill", AddQuickHealTargetSkill);
	lua_register(getLuaState(), "AddMindHealTargetSkill", AddMindHealTargetSkill);
	lua_register(getLuaState(), "AddDragTargetSkill", AddDragTargetSkill);

	lua_register(getLuaState(), "AddDeBuffAttackTargetSkill", AddDeBuffAttackTargetSkill);
	lua_register(getLuaState(), "AddEnhanceSelfSkill", AddEnhanceSelfSkill);
	lua_register(getLuaState(), "AddDotPoolAttackTargetSkill", AddDotPoolAttackTargetSkill);
	lua_register(getLuaState(), "AddChangePostureSelfSkill", AddChangePostureSelfSkill);
	//lua_register(getLuaState(), "AddWoundsDirectPoolAttackTargetSkill", AddWoundsDirectPoolAttackTargetSkill);
	lua_register(getLuaState(), "AddPassiveSkill", AddPassiveSkill);
	lua_register(getLuaState(), "AddMeditateSkill", AddMeditateSkill);
	lua_register(getLuaState(), "AddPowerboostSkill", AddPowerboostSkill);
	lua_register(getLuaState(), "AddEntertainSkill", AddEntertainSkill);
	lua_register(getLuaState(), "AddEntertainEffectSkill", AddEntertainEffectSkill);
	lua_register(getLuaState(), "AddBandFlourishSkill", AddBandFlourishSkill);
	lua_register(getLuaState(), "AddDanceEffectSkill", AddDanceEffectSkill);
	lua_register(getLuaState(), "AddMusicEffectSkill", AddMusicEffectSkill);
	lua_register(getLuaState(), "AddForceRunSelfSkill", AddForceRunSelfSkill);
	lua_register(getLuaState(), "AddDiagnoseTargetSkill", AddDiagnoseTargetSkill);

	lua_register(getLuaState(), "AddCamoSkill", AddCamoSkill);
	lua_register(getLuaState(), "AddForageSkill", AddForageSkill);
	lua_register(getLuaState(), "AddAreaTrackSkill", AddAreaTrackSkill);
	lua_register(getLuaState(), "AddThrowRandomPoolTargetSkill", AddThrowRandomPoolTargetSkill);
	lua_register(getLuaState(), "AddThrowDirectPoolTargetSkill", AddThrowDirectPoolTargetSkill);
	lua_register(getLuaState(), "AddThrowGrenadeTargetSkill", AddThrowGrenadeTargetSkill);

	// Squad Leader skills
	lua_register(getLuaState(), "AddBoostMoraleGroupSkill", AddBoostMoraleGroupSkill);
	lua_register(getLuaState(), "AddFormupGroupSkill", AddFormupGroupSkill);
	lua_register(getLuaState(), "AddRallyGroupSkill", AddRallyGroupSkill);
	lua_register(getLuaState(), "AddRetreatGroupSkill", AddRetreatGroupSkill);
	//lua_register(getLuaState(), "AddSteadyAimGroupSkill", AddSteadyAimGroupSkill);
	lua_register(getLuaState(), "AddVolleyFireGroupSkill", AddVolleyFireGroupSkill);
	lua_register(getLuaState(), "AddSystemGroupMessageSkill", AddSystemGroupMessageSkill);

	lua_register(getLuaState(), "AddCMDotAttackTargetSkill", AddCMDotAttackTargetSkill);

}

void ScriptAttacksManager::registerGlobals() {

	//states
	setGlobalLong("INVALID_STATE", CreatureState::INVALID);
	setGlobalLong("COVER_STATE", CreatureState::COVER);
	setGlobalLong("COMBAT_STATE", CreatureState::COMBAT);
	setGlobalLong("PEACE_STATE", CreatureState::PEACE);
	setGlobalLong("AIMING_STATE", CreatureState::AIMING);
	setGlobalLong("ALERT_STATE", CreatureState::ALERT);
	setGlobalLong("BERSERK_STATE", CreatureState::BERSERK);
	setGlobalLong("FEIGNDEATH_STATE", CreatureState::FEIGNDEATH);
	setGlobalLong("COMBATATTITUDEEVASIVE_STATE", CreatureState::COMBATATTITUDEEVASIVE);
	setGlobalLong("COMBATATTITUDENORMAL_STATE", CreatureState::COMBATATTITUDENORMAL);
	setGlobalLong("COMBATATTITUDEAGGRESSIVE_STATE", CreatureState::COMBATATTITUDEAGGRESSIVE);
	setGlobalLong("TUMBLING_STATE", CreatureState::TUMBLING);
	setGlobalLong("RALLIED_STATE", CreatureState::RALLIED);
	setGlobalLong("STUNNED_STATE", CreatureState::STUNNED);
	setGlobalLong("BLINDED_STATE", CreatureState::BLINDED);
	setGlobalLong("DIZZY_STATE",  CreatureState::DIZZY);
	setGlobalLong("INTIMIDATED_STATE", CreatureState::INTIMIDATED);
	setGlobalLong("IMMOBILIZED_STATE", CreatureState::SNARED);
	setGlobalLong("FROZEN_STATE", CreatureState::ROOTED);
	setGlobalLong("SWIMMING_STATE", CreatureState::SWIMMING);
	setGlobalLong("SITTINGONCHAIR_STATE", CreatureState::SITTINGONCHAIR);
	setGlobalLong("CRAFTING_STATE", CreatureState::CRAFTING);
	setGlobalLong("GLOWINGJEDI_STATE", CreatureState::GLOWINGJEDI);
	setGlobalLong("MASKSCENT_STATE", CreatureState::MASKSCENT);
	setGlobalLong("POISONED_STATE", CreatureState::POISONED);
	setGlobalLong("BLEEDING_STATE", CreatureState::BLEEDING);
	setGlobalLong("DISEASED_STATE", CreatureState::DISEASED);
	setGlobalLong("ONFIRE_STATE", CreatureState::ONFIRE);
	setGlobalLong("RIDINGMOUNT_STATE", CreatureState::RIDINGMOUNT);
	setGlobalLong("MOUNTEDCREATURE_STATE", CreatureState::MOUNTEDCREATURE);
	setGlobalLong("PILOTSHIP_STATE", CreatureState::PILOTSHIP);
	setGlobalLong("SHIPOPERATIONS_STATE", CreatureState::SHIPOPERATIONS);
	setGlobalLong("SHIPGUNNER_STATE", CreatureState::SHIPGUNNER);

	//TODO: remove this - there is no centered state?
	setGlobalLong("CENTERED_STATE", 0x80000000);

	//TODO: What is this? Can it be removed? who thought 0x123 would be a mask?
	setGlobalLong("MEDITATE", 0x123);

	// postures

	setGlobalInt("INVALID_POSTURE", CreaturePosture::INVALID);
	setGlobalInt("UPRIGHT_POSTURE", CreaturePosture::UPRIGHT);
	setGlobalInt("CROUCHED_POSTURE", CreaturePosture::CROUCHED);
	setGlobalInt("PRONE_POSTURE", CreaturePosture::PRONE);
	setGlobalInt("SNEAKING_POSTURE", CreaturePosture::SNEAKING);
	setGlobalInt("BLOCKING_POSTURE", CreaturePosture::BLOCKING);
	setGlobalInt("CLIMBING_POSTURE", CreaturePosture::CLIMBING);
	setGlobalInt("FLYING_POSTURE", CreaturePosture::FLYING);
	setGlobalInt("LYINGDOWN_POSTURE", CreaturePosture::LYINGDOWN);
	setGlobalInt("SITTING_POSTURE", CreaturePosture::SITTING);
	setGlobalInt("SKILLANIMATING_POSTURE", CreaturePosture::SKILLANIMATING);
	setGlobalInt("DRIVINGVEHICLE_POSTURE", CreaturePosture::DRIVINGVEHICLE);
	setGlobalInt("RIDINGCREATURE_POSTURE", CreaturePosture::RIDINGCREATURE);
	setGlobalInt("KNOCKEDDOWN_POSTURE", CreaturePosture::KNOCKEDDOWN);
	setGlobalInt("INCAPACITATED_POSTURE", CreaturePosture::INCAPACITATED);
	setGlobalInt("DEAD_POSTURE", CreaturePosture::DEAD);

	// weapons
	setGlobalInt("ALL", 0xFF);
	setGlobalInt("MELEE", 0x10);
	setGlobalInt("RANGED", 0x20);
	setGlobalInt("JEDI", 0x30);

	setGlobalInt("UNARMED", 0);
	setGlobalInt("ONEHANDED", 1);
	setGlobalInt("TWOHANDED", 2);
	setGlobalInt("POLEARM", 3);
	setGlobalInt("PISTOL", 4);
	setGlobalInt("CARBINE", 5);
	setGlobalInt("RIFLE", 6);
	setGlobalInt("ONEHANDSABER", 7);
	setGlobalInt("TWOHANDSABER", 8);
	setGlobalInt("POLEARMSABER", 9);
	setGlobalInt("RIFLEBEAM", 10);
	setGlobalInt("RIFLEFLAMETHROWER", 11);
	setGlobalInt("RIFLELIGHTNING", 12);
	setGlobalInt("RIFLEACIDBEAM", 13);
	setGlobalInt("HEAVYACIDBEAM", 14);
	setGlobalInt("HEAVYLIGHTNINGBEAM", 15);
	setGlobalInt("HEAVYPARTICLEBEAM", 17);
	setGlobalInt("HEAVYROCKETLAUNCHER", 18);
	setGlobalInt("HEAVYLAUNCHER", 19);
	setGlobalInt("GRENADE", 20);

	setGlobalInt("NONE", 0xFF);

	// Jedi Power attack types
	setGlobalInt("FORCETHROW", 1);
	setGlobalInt("FORCELIGHTNING", 2);
	setGlobalInt("MINDBLAST", 3);
	setGlobalInt("FORCEKNOCKDOWN", 4);
	setGlobalInt("FORCECHOKE", 5);
	setGlobalInt("FORCEWEAKEN", 6);
	setGlobalInt("FORCEINTIMIDATE", 7);

	// Damage type for powers
	setGlobalInt("KINETIC", WeaponImplementation::KINETIC);
	setGlobalInt("ELECTRICITY", WeaponImplementation::ELECTRICITY);


	// misc
	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("STRENGTH", CreatureAttribute::STRENGTH);
	setGlobalInt("CONSTITUTION", CreatureAttribute::CONSTITUTION);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("QUICKNESS", CreatureAttribute::QUICKNESS);
	setGlobalInt("STAMINA", CreatureAttribute::STAMINA);
	setGlobalInt("MIND", CreatureAttribute::MIND);
	setGlobalInt("FOCUS", CreatureAttribute::FOCUS);
	setGlobalInt("WILLPOWER", CreatureAttribute::WILLPOWER);

	// CM items
	setGlobalInt("POISONDELIVERYUNIT", PharmaceuticalImplementation::POISONDELIVERYUNIT);
	setGlobalInt("DISEASEDELIVERYUNIT", PharmaceuticalImplementation::DISEASEDELIVERYUNIT);
}

int ScriptAttacksManager::AddRandomPoolAttackTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	AttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int postureUpStateChance = skill.getIntField("postureUpChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	float healthCostMultiplier = skill.getFloatField("healthCostMultiplier");
	float actionCostMultiplier = skill.getFloatField("actionCostMultiplier");
	float mindCostMultiplier = skill.getFloatField("mindCostMultiplier");
	float forceCostMultiplier = skill.getFloatField("forceCostMultiplier");

	// For force powers
	int forceCost = skill.getIntField("forceCost");

	attack = new RandomPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setPostureUpChance(postureUpStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setHealthCostMultiplier(healthCostMultiplier);
	attack->setActionCostMultiplier(actionCostMultiplier);
	attack->setMindCostMultiplier(mindCostMultiplier);
	attack->setForceCostMultiplier(forceCostMultiplier);

	CombatActions->put(attack);
	return 0;
}

int ScriptAttacksManager::AddDirectPoolAttackTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	AttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int healthPoolAttackChance = skill.getIntField("healthAttackChance");
	int strengthPoolAttackChance = skill.getIntField("strengthAttackChance");
	int constitutionPoolAttackChance = skill.getIntField("constitutionAttackChance");

	int actionPoolAttackChance = skill.getIntField("actionAttackChance");
	int quicknessPoolAttackChance = skill.getIntField("quicknessPoolAttackChance");
	int staminaPoolAttackChance = skill.getIntField("staminaPoolAttackChance");

	int mindPoolAttackChance = skill.getIntField("mindAttackChance");
	int focusPoolAttackChance = skill.getIntField("focusAttackChance");
	int willpowerPoolAttackChance = skill.getIntField("willpowerAttackChance");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	float healthCostMultiplier = skill.getFloatField("healthCostMultiplier");
	float actionCostMultiplier = skill.getFloatField("actionCostMultiplier");
	float mindCostMultiplier = skill.getFloatField("mindCostMultiplier");
	float forceCostMultiplier = skill.getFloatField("forceCostMultiplier");

	attack = new DirectPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);

	attack->setHealthPoolAttackRatio(healthPoolAttackChance);
	attack->setStrengthPoolAttackRatio(strengthPoolAttackChance);
	attack->setConstitutionPoolAttackRatio(constitutionPoolAttackChance);

	attack->setActionPoolAttackRatio(actionPoolAttackChance);
	attack->setQuicknessPoolAttackRatio(quicknessPoolAttackChance);
	attack->setStaminaPoolAttackRatio(staminaPoolAttackChance);

	attack->setMindPoolAttackRatio(mindPoolAttackChance);
	attack->setFocusPoolAttackRatio(focusPoolAttackChance);
	attack->setWillpowerPoolAttackRatio(willpowerPoolAttackChance);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setHealthCostMultiplier(healthCostMultiplier);
	attack->setActionCostMultiplier(actionCostMultiplier);
	attack->setMindCostMultiplier(mindCostMultiplier);
	attack->setForceCostMultiplier(forceCostMultiplier);

	CombatActions->put(attack);
	return 0;
}


int ScriptAttacksManager::AddDotPoolAttackTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	DotPoolAttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");
	int knockDownChance = skill.getIntField("knockdownChance");
	int postureDownChance = skill.getIntField("postureDownChance");
	int dizzyChance = skill.getIntField("dizzyChance");

	int healthPoolAttackChance = skill.getIntField("healthAttackChance");
	int actionPoolAttackChance = skill.getIntField("actionAttackChance");
	int mindPoolAttackChance = skill.getIntField("mindAttackChance");

	int dotStateChance = skill.getIntField("dotChance");
	int tickStrengthOfHit = skill.getIntField("tickStrengthOfHit");

	int fireStrength = skill.getIntField("fireStrength");
	int fireType = skill.getIntField("fireType");

	int bleedingStrength = skill.getIntField("bleedingStrength");
	int bleedingType = skill.getIntField("bleedingType");

	int poisonStrength = skill.getIntField("poisonStrength");
	int poisonType = skill.getIntField("poisonType");

	int diseaseStrength = skill.getIntField("diseaseStrength");
	int diseaseType = skill.getIntField("diseaseType");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	float healthCostMultiplier = skill.getFloatField("healthCostMultiplier");
	float actionCostMultiplier = skill.getFloatField("actionCostMultiplier");
	float mindCostMultiplier = skill.getFloatField("mindCostMultiplier");
	float forceCostMultiplier = skill.getFloatField("forceCostMultiplier");


	attack = new DotPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);
	attack->setPostureDownChance(postureDownChance);
	attack->setKnockdownChance(knockDownChance);
	attack->setDizzyChance(dizzyChance);

	attack->setHealthPoolAttackRatio(healthPoolAttackChance);
	attack->setActionPoolAttackRatio(actionPoolAttackChance);
	attack->setMindPoolAttackRatio(mindPoolAttackChance);

    attack->setDotChance(dotStateChance);
    attack->setTickStrengthOfHit(tickStrengthOfHit);

    attack->setFireDotStrength(fireStrength);
    attack->setFireDotType(fireType);

    attack->setBleedingDotStrength(bleedingStrength);
    attack->setBleedingDotType(bleedingType);

    attack->setPoisonDotStrength(poisonStrength);
    attack->setPoisonDotType(poisonType);

    attack->setDiseaseDotStrength(diseaseStrength);
    attack->setDiseaseDotType(diseaseType);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setHealthCostMultiplier(healthCostMultiplier);
	attack->setActionCostMultiplier(actionCostMultiplier);
	attack->setMindCostMultiplier(mindCostMultiplier);
	attack->setForceCostMultiplier(forceCostMultiplier);

	CombatActions->put(attack);
	return 0;
}
/*
int ScriptAttacksManager::AddWeaponlessDotPoolAttackSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	WeaponlessDotPoolAttackSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int weaponType = skill.getIntField("requiredWeaponType");

	int forceCost = skill.getIntField("forceCost");
	int mindCost = skill.getIntField("mindCost");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");
	int postureDownChance = skill.getIntField("postureDownChance");

	int healthPoolAttackChance = skill.getIntField("healthAttackChance");
	int actionPoolAttackChance = skill.getIntField("actionAttackChance");
	int mindPoolAttackChance = skill.getIntField("mindAttackChance");

	int dotStateChance = skill.getIntField("dotChance");
	int tickStrengthOfHit = skill.getIntField("tickStrengthOfHit");

	int fireStrength = skill.getIntField("fireStrength");
	int fireType = skill.getIntField("fireType");

	int bleedingStrength = skill.getIntField("bleedingStrength");
	int bleedingType = skill.getIntField("bleedingType");

	int poisonStrength = skill.getIntField("poisonStrength");
	int poisonType = skill.getIntField("poisonType");

	int diseaseStrength = skill.getIntField("diseaseStrength");
	int diseaseType = skill.getIntField("diseaseType");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");


	attack = new WeaponlessDotPoolAttackSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);
	attack->setPostureDownChance(postureDownChance);

	attack->setHealthPoolAttackRatio(healthPoolAttackChance);
	attack->setActionPoolAttackRatio(actionPoolAttackChance);
	attack->setMindPoolAttackRatio(mindPoolAttackChance);

    attack->setDotChance(dotStateChance);
    attack->setTickStrengthOfHit(tickStrengthOfHit);

    attack->setFireDotStrength(fireStrength);
    attack->setFireDotType(fireType);

    attack->setBleedingDotStrength(bleedingStrength);
    attack->setBleedingDotType(bleedingType);

    attack->setPoisonDotStrength(poisonStrength);
    attack->setPoisonDotType(poisonType);

    attack->setDiseaseDotStrength(diseaseStrength);
    attack->setDiseaseDotType(diseaseType);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	CombatActions->put(attack);
	return 0;
}
*/
int ScriptAttacksManager::AddForcePowersPoolAttackTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ForcePowersPoolAttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int attackType = skill.getIntField("attackType");
	int forceCost = skill.getIntField("forceCost");

	int damageType = skill.getIntField("damageType");
	float minDamage = skill.getFloatField("minDamage");
	float maxDamage = skill.getFloatField("maxDamage");

	float speed = skill.getFloatField("speed");

	int range = skill.getIntField("range");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");


	attack = new ForcePowersPoolAttackTargetSkill(attackname, animation, server);
	attack->setForceCost(forceCost);

	attack->setAttackType(attackType);
	attack->setDamageType(damageType);
	attack->setMinDamage(minDamage);
	attack->setMaxDamage(maxDamage);

	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);

	if (speed < 1.0f)
		speed = 4.0f;
	attack->setSpeed(speed);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	CombatActions->put(attack);
	return 0;
}

int ScriptAttacksManager::AddForceHealSelfSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ForceHealSelfSkill* fheal;

	String skillname = skill.getStringField("skillname");
	//String animation = getStringField("animation");
	String effect = skill.getStringField("effect");

	int forceCost = skill.getIntField("forceCost");
	int healHealth = skill.getIntField("HealHealth");
	int healAction = skill.getIntField("HealAction");
	int healMind = skill.getIntField("HealMind");

	float speed = skill.getFloatField("speed");

	bool healDizzy = skill.getIntField("healDizzy");
	bool healStun = skill.getIntField("healStun");
	bool healBlind = skill.getIntField("healBlind");
	bool healIntimidate = skill.getIntField("healIntimidate");

	bool healPoison = skill.getIntField("healPoison");
	bool healDisease = skill.getIntField("healDisease");
	bool healFire = skill.getIntField("healFire");
	bool healBleeding = skill.getIntField("healBleeding");

	fheal = new ForceHealSelfSkill(skillname, effect.toCharArray(), server);

	fheal->setForceCost(forceCost);
	fheal->setHealHealth(healHealth);
	fheal->setHealAction(healAction);
	fheal->setHealMind(healMind);
	fheal->setSpeed(speed);

	fheal->setHealDizzy(healDizzy);
	fheal->setHealStun(healStun);
	fheal->setHealBlind(healBlind);
	fheal->setHealIntimidate(healIntimidate);

	fheal->setHealPoison(healPoison);
	fheal->setHealFire(healFire);
	fheal->setHealBleeding(healBleeding);
	fheal->setHealDisease(healDisease);

	CombatActions->put(fheal);
	return 0;
}

int ScriptAttacksManager::AddHealSelfSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealSelfSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int healHealth = skill.getIntField("healHealth");
	int healAction = skill.getIntField("healAction");
	int healMind = skill.getIntField("healMind");

	float speed = skill.getFloatField("speed");

	bool healDizzy = skill.getIntField("healDizzy");
	bool healStun = skill.getIntField("healStun");
	bool healBlind = skill.getIntField("healBlind");
	bool healIntimidate = skill.getIntField("healIntimidate");

	bool healPoison = skill.getIntField("healPoison");
	bool healDisease = skill.getIntField("healDisease");
	bool healFire = skill.getIntField("healFire");
	bool healBleeding = skill.getIntField("healBleeding");

	heal = new HealSelfSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);

	heal->setHealHealth(healHealth);
	heal->setHealAction(healAction);
	heal->setHealMind(healMind);

	heal->setSpeed(speed);

	heal->setHealDizzy(healDizzy);
	heal->setHealStun(healStun);
	heal->setHealBlind(healBlind);
	heal->setHealIntimidate(healIntimidate);

	heal->setHealPoison(healPoison);
	heal->setHealFire(healFire);
	heal->setHealBleeding(healBleeding);
	heal->setHealDisease(healDisease);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddHealTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int healHealth = skill.getIntField("healHealth");
	int healAction = skill.getIntField("healAction");
	int healMind = skill.getIntField("healMind");

	float speed = skill.getFloatField("speed");

	bool healDizzy = skill.getIntField("healDizzy");
	bool healStun = skill.getIntField("healStun");
	bool healBlind = skill.getIntField("healBlind");
	bool healIntimidate = skill.getIntField("healIntimidate");

	bool healPoison = skill.getIntField("healPoison");
	bool healDisease = skill.getIntField("healDisease");
	bool healFire = skill.getIntField("healFire");
	bool healBleeding = skill.getIntField("healBleeding");

	int range = skill.getIntField("range");

	heal = new HealTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);

	heal->setRange(range);

	heal->setHealHealth(healHealth);
	heal->setHealAction(healAction);
	heal->setHealMind(healMind);

	heal->setSpeed(speed);

	heal->setHealDizzy(healDizzy);
	heal->setHealStun(healStun);
	heal->setHealBlind(healBlind);
	heal->setHealIntimidate(healIntimidate);

	heal->setHealPoison(healPoison);
	heal->setHealFire(healFire);
	heal->setHealBleeding(healBleeding);
	heal->setHealDisease(healDisease);

	CombatActions->put(heal);
	return 0;
}


int ScriptAttacksManager::AddHealEnhanceTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealEnhanceTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	heal = new HealEnhanceTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);


	CombatActions->put(heal);

	return 0;
}

int ScriptAttacksManager::AddHealWoundTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealWoundTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	heal = new HealWoundTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddFirstAidTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	FirstAidTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float speed = skill.getFloatField("speed");
	float range = skill.getFloatField("range");

	heal = new FirstAidTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setSpeed(speed);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddCureTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	CureTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	uint64 conditionCured = skill.getLongField("conditionCured");
	float range = skill.getFloatField("range");

	heal = new CureTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setState(conditionCured);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddHealStateTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealStateTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	heal = new HealStateTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddHealDamageTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	HealDamageTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	heal = new HealDamageTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}


int ScriptAttacksManager::AddReviveTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ReviveTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	heal = new ReviveTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddTendHealTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	TendHealTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	int mindWoundCost = skill.getIntField("mindWoundCost");
	float range = skill.getFloatField("range");
	float speed = skill.getFloatField("speed");

	int healthHealed = skill.getIntField("healthHealed");
	int actionHealed = skill.getIntField("actionHealed");
	int mindHealed = skill.getIntField("mindHealed");

	int woundPool = skill.getIntField("woundPool");
	int woundsHealed = skill.getIntField("woundsHealed");

	bool tendDamage = skill.getIntField("tendDamage");
	bool tendWound = skill.getIntField("tendWound");

	heal = new TendHealTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setMindWoundCost(mindWoundCost);
	heal->setRange(range);
	heal->setSpeed(speed);

	heal->setHealthHealed(healthHealed);
	heal->setActionHealed(actionHealed);
	heal->setMindHealed(mindHealed);

	heal->setWoundPool(woundPool);
	heal->setWoundsHealed(woundsHealed);

	heal->setTendDamage(tendDamage);
	heal->setTendWound(tendWound);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddQuickHealTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	QuickHealTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	int mindWoundCost = skill.getIntField("mindWoundCost");
	float range = skill.getFloatField("range");
	float speed = skill.getFloatField("speed");

	int healthHealed = skill.getIntField("healthHealed");
	int actionHealed = skill.getIntField("actionHealed");
	int mindHealed = skill.getIntField("mindHealed");

	heal = new QuickHealTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setMindWoundCost(mindWoundCost);
	heal->setRange(range);
	heal->setSpeed(speed);

	heal->setHealthHealed(healthHealed);
	heal->setActionHealed(actionHealed);
	heal->setMindHealed(mindHealed);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddMindHealTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	MindHealTargetSkill* heal;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");
	float speed = skill.getFloatField("speed");

	heal = new MindHealTargetSkill(skillname, effect.toCharArray(), server);
	heal->setSecondaryAnim(animation);
	heal->setMindCost(mindCost);
	heal->setRange(range);
	heal->setSpeed(speed);

	CombatActions->put(heal);
	return 0;
}

int ScriptAttacksManager::AddDragTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	DragTargetSkill* drag;

	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effect");
	float maxRange = skill.getFloatField("maxRange");
	float maxMovement = skill.getFloatField("maxMovement");
	float speed = skill.getFloatField("speed");
	bool needsConsent = skill.getIntField("needsConsent");

	drag = new DragTargetSkill(skillname, effect.toCharArray(), server);

	drag->setMaxRange(maxRange);
	drag->setMaxMovement(maxMovement);
	drag->setSpeed(speed);
	drag->setNeedsConsent(needsConsent);
	drag->setRange(130.0f);

	CombatActions->put(drag);
	return 0;
}

int ScriptAttacksManager::AddDeBuffAttackTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	DeBuffAttackTargetSkill* attSkill;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");

	int range = skill.getIntField("range");
	int areaRange = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");

	float duration = skill.getFloatField("duration");

	float speed = skill.getFloatField("speedRatio");

	int forceCost = skill.getIntField("forceCost");

	int meleeDamagePenalty = skill.getIntField("meleeDamagePenalty");
	int meleeAccuracyPenalty = skill.getIntField("meleeAccuracyPenalty");

	int rangedDamagePenalty = skill.getIntField("rangedDamagePenalty");
	int rangedAccuracyPenalty = skill.getIntField("rangedAccuracyPenalty");

	int DefensePenalty = skill.getIntField("defensePenalty");
	int SpeedPenalty = skill.getIntField("speedPenalty");

	float nextAttackDelay = skill.getFloatField("nextAttackDelay");

	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");

	String selfeffect = skill.getStringField("selfEffect");

	String flytext = skill.getStringField("FlyText");

	attSkill = new DeBuffAttackTargetSkill(skillname, animation, server);

	attSkill->setSpeed(speed);
	attSkill->setRange(range);
	attSkill->setAreaRangeDamage(areaRange);
	attSkill->setConeAngle(cone);
	attSkill->setDuration(duration);

	attSkill->setForceCost(forceCost);

	attSkill->setMeleeDamagePenalty(meleeDamagePenalty);
	attSkill->setMeleeAccuracyPenalty(meleeAccuracyPenalty);

	attSkill->setRangedDamagePenalty(rangedDamagePenalty);
	attSkill->setRangedAccuracyPenalty(rangedAccuracyPenalty);

	attSkill->setDefensePenalty(DefensePenalty);
	attSkill->setSpeedPenalty(SpeedPenalty);

	attSkill->setDizzyChance(dizzyStateChance);
	attSkill->setBlindChance(blindStateChance);
	attSkill->setStunChance(stunStateChance);
	attSkill->setIntimidateChance(intimidateStateChance);

	attSkill->setNextAttackDelay(nextAttackDelay);

	attSkill->setSelfEffect(selfeffect);

	attSkill->setFlyText(flytext);

	CombatActions->put(attSkill);

	return 0;
}

int ScriptAttacksManager::AddEnhanceSelfSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	EnhanceSelfSkill* Skill;

	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effect");

	int cone = skill.getIntField("coneAngle");

	float duration = skill.getFloatField("duration");

	float speed = skill.getFloatField("speed");

	int healthBonus = skill.getIntField("healthBonus");
	int actionBonus = skill.getIntField("actionBonus");
	int mindBonus = skill.getIntField("mindBonus");

	int requiredState = skill.getIntField("requiredState");

	int damageBonus = skill.getIntField("damageBonus");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int defenseBonus = skill.getIntField("defenseBonus");
	int speedBonus = skill.getIntField("speedBonus");

	String startflytext = skill.getStringField("StartFlyText");
	String finishflytext = skill.getStringField("FinishFlyText");

	Skill = new EnhanceSelfSkill(skillname, effect.toCharArray(), server);

	Skill->setSpeed(speed);
	Skill->setDuration(duration);

	Skill->setHealthBonus(healthBonus);
	Skill->setActionBonus(actionBonus);
	Skill->setMindBonus(mindBonus);

	Skill->setDamageBonus(damageBonus);
	Skill->setAccuracyBonus(accuracyBonus);

	Skill->setDefenseBonus(defenseBonus);
	Skill->setSpeedBonus(speedBonus);

	Skill->setRequiredState(requiredState);

	Skill->setFlyText(startflytext, finishflytext);

	CombatActions->put(Skill);


	return 0;
}

int ScriptAttacksManager::AddChangePostureSelfSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ChangePostureSelfSkill* Skill;

	String skillname = skill.getStringField("skillname");
	String anim = skill.getStringField("animation");

	float speed = skill.getFloatField("speed");

	uint8 posture = (uint8)skill.getIntField("posture");

	Skill = new ChangePostureSelfSkill(skillname, anim, server);

	Skill->setSpeed(speed);
	Skill->setPosture(posture);

	CombatActions->put(Skill);

	return 0;
}
/*
int ScriptAttacksManager::AddWoundsDirectPoolAttackTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	AttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int accuracyBonus = skill.getIntField("accuracyBonus");
	int cone = skill.getIntField("coneAngle");

	int healthAttackChance = skill.getIntField("healthAttackChance");
	int actionAttackChance = skill.getIntField("actionAttackChance");
	int mindAttackChance = skill.getIntField("mindAttackChance");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	float healthCostMultiplier = skill.getFloatField("healthCostMultiplier");
	float actionCostMultiplier = skill.getFloatField("actionCostMultiplier");
	float mindCostMultiplier = skill.getFloatField("mindCostMultiplier");
	float forceCostMultiplier = skill.getFloatField("forceCostMultiplier");

	attack = new WoundsDirectPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);
	attack->setConeAngle(cone);

	attack->setHealthPoolAttackRatio(healthAttackChance);
	attack->setActionPoolAttackRatio(actionAttackChance);
	attack->setMindPoolAttackRatio(mindAttackChance);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setHealthCostMultiplier(healthCostMultiplier);
	attack->setActionCostMultiplier(actionCostMultiplier);
	attack->setMindCostMultiplier(mindCostMultiplier);
	attack->setForceCostMultiplier(forceCostMultiplier);


	CombatActions->put(attack);
	return 0;
}
*/
int ScriptAttacksManager::RunSkillsFile(lua_State* L) {
	String filename;

	filename = getStringParameter(L);

	runFile("scripts/skills/" + filename, L);

	return 0;
}

int ScriptAttacksManager::AddPassiveSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	PassiveSkill* Skill;

	String skillname = skill.getStringField("skillname");

	int damageReduction = skill.getIntField("damageReduction");

	Skill = new PassiveSkill(skillname, server);
	Skill->setDamageReduction(damageReduction);

	CombatActions->put(Skill);

	return 0;
}

int ScriptAttacksManager::AddMeditateSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	MeditateSelfSkill* meditate;
	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effectname");

	meditate = new MeditateSelfSkill(skillname, effect, server);
	CombatActions->put(meditate);

	return 0;
}

int ScriptAttacksManager::AddPowerboostSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effect");
	float bonus = skill.getFloatField("bonus");

	PowerboostSelfSkill* powerboost = new PowerboostSelfSkill(skillname, effect.toCharArray(), server);
	powerboost->setBonus(bonus);
	CombatActions->put(powerboost);

	return 0;
}

int ScriptAttacksManager::AddEntertainSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	EntertainSelfSkill* entertain;
	String skillname = skill.getStringField("skillname");

	entertain = new EntertainSelfSkill(skillname, server);
	CombatActions->put(entertain);

	return 0;
}

int ScriptAttacksManager::AddEntertainEffectSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	EntertainEffectSelfSkill* entertain;
	String skillname = skill.getStringField("skillname");

	String effect_prefix = skill.getStringField("effect_prefix");

	entertain = new EntertainEffectSelfSkill(skillname, effect_prefix, server);
	CombatActions->put(entertain);

	return 0;
}

int ScriptAttacksManager::AddBandFlourishSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	String skillname = skill.getStringField("skillname");

	BandFlourishSkill* bandflo;
	bandflo = new BandFlourishSkill(skillname, server);
	CombatActions->put(bandflo);

	return 0;
}

int ScriptAttacksManager::AddDanceEffectSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	DanceEffectSelfSkill* dance;
	String skillname = skill.getStringField("skillname");

	String effect_prefix = skill.getStringField("effect_prefix");

	dance = new DanceEffectSelfSkill(skillname, effect_prefix, server);
	CombatActions->put(dance);

	return 0;
}

int ScriptAttacksManager::AddMusicEffectSkill(lua_State* L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	MusicEffectSelfSkill* music;
	String skillname = skill.getStringField("skillname");

	String effect_prefix = skill.getStringField("effect_prefix");

	music = new MusicEffectSelfSkill(skillname, effect_prefix, server);
	CombatActions->put(music);

	return 0;
}

int ScriptAttacksManager::AddForceRunSelfSkill(lua_State *L) {
	LuaObject skill(L);
	if (!skill.isValidTable())
		return 0;

	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effect");

	int forceCost = skill.getIntField("forceCost");
	float speed = skill.getFloatField("speed");
	float acceleration = skill.getFloatField("acceleration");
	int slope = skill.getIntField("slope");
	int duration = skill.getIntField("duration");


	ForceRunSelfSkill* frun = new ForceRunSelfSkill(skillname, effect, speed, acceleration, slope, duration, server);

	frun->setForceCost(forceCost);

	CombatActions->put(frun);
	return 0;
}

int ScriptAttacksManager::AddDiagnoseTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	DiagnoseTargetSkill* diagnose;

	String skillname = skill.getStringField("skillname");
	String animation = skill.getStringField("animation");
	String effect = skill.getStringField("effect");

	int mindCost = skill.getIntField("mindCost");
	float range = skill.getFloatField("range");

	diagnose = new DiagnoseTargetSkill(skillname, effect.toCharArray(), server);
	diagnose->setSecondaryAnim(animation);
	diagnose->setMindCost(mindCost);
	diagnose->setRange(range);


	CombatActions->put(diagnose);
	return 0;
}

int ScriptAttacksManager::AddCamoSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	String skillname = skill.getStringField("skillname");
	int type = skill.getIntField("type");
	float duration = skill.getFloatField("duration");

	CamoSkill* Skill ;
	if (type == 1)
		Skill = new MaskScentSelfSkill(skillname, server);
	if (type == 2)
		Skill = new ConcealSkill(skillname, server);

	Skill->setDuration(duration);

	CombatActions->put(Skill);

	return 0;
}

int ScriptAttacksManager::AddForageSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	String skillName = skill.getStringField("skillName");
	String animation = skill.getStringField("animation");
	int actionCost = skill.getIntField("actionCost");

	ForageSelfSkill* forage;
	forage = new ForageSelfSkill(skillName, animation, server);

	actionCost = abs(actionCost);
	forage->setActionCost(actionCost);

	if (skillName == "forage") {
		forage->setSkill(0);
	} else if (skillName == "medicalforage") {
		forage->setSkill(1);
	} else {
		System::out << "[ERROR] when attempting to add a forage skill. The skillName in the lua is incorrect!" << endl;
	}

	CombatActions->put(forage);
	return 0;
}

int ScriptAttacksManager::AddSystemGroupMessageSkill(lua_State* L) {
	LuaObject skill(L);

	try {

		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = "";

		SystemGroupMessageSkill* sysgroup;
		sysgroup = new SystemGroupMessageSkill(skillName, animation, server);

		CombatActions->put(sysgroup);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add SystemMessageGroupSkill!" << endl;
		return -1;
	}
}

int ScriptAttacksManager::AddBoostMoraleGroupSkill(lua_State* L) {
	LuaObject skill(L);

	try {

		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = "";
		String combatSpam = skill.getStringField("combatspam");
		int cooldownTime = skill.getIntField("cooldowntime");
		int healthCost = skill.getIntField("healthcost");
		int actionCost = skill.getIntField("actioncost");
		int mindCost = skill.getIntField("mindcost");

		BoostMoraleGroupSkill* boostMorale;
		boostMorale = new BoostMoraleGroupSkill(skillName, animation, server);
		boostMorale->setCombatSpam(combatSpam);
		boostMorale->setCooldownTime(cooldownTime);
		boostMorale->setHealthCost(healthCost);
		boostMorale->setActionCost(actionCost);
		boostMorale->setMindCost(mindCost);

		CombatActions->put(boostMorale);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add BoostMoraleGroupSkill!" << endl;
		return -1;
	}
}

int ScriptAttacksManager::AddVolleyFireGroupSkill(lua_State* L) {
	LuaObject skill(L);

	try {

		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = "";
		String combatSpam = skill.getStringField("combatspam");
		String defaultAttack = skill.getStringField("defaultattack");
		int cooldownTime = skill.getIntField("cooldowntime");
		int healthCost = skill.getIntField("healthcost");
		int actionCost = skill.getIntField("actioncost");
		int mindCost = skill.getIntField("mindcost");

		VolleyFireGroupSkill* volleyFire;
		volleyFire = new VolleyFireGroupSkill(skillName, animation, server);
		volleyFire->setCombatSpam(combatSpam);
		volleyFire->setDefaultAttack(defaultAttack);
		volleyFire->setCooldownTime(cooldownTime);
		volleyFire->setHealthCost(healthCost);
		volleyFire->setActionCost(actionCost);
		volleyFire->setMindCost(mindCost);

		CombatActions->put(volleyFire);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add AddVolleyFireGroupSkill!" << endl;
		return -1;
	}
}

int ScriptAttacksManager::AddFormupGroupSkill(lua_State* L) {
	LuaObject skill(L);

	try {

		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = "";
		String combatSpam = skill.getStringField("combatspam");
		int cooldownTime = skill.getIntField("cooldowntime");
		int healthCost = skill.getIntField("healthcost");
		int actionCost = skill.getIntField("actioncost");
		int mindCost = skill.getIntField("mindcost");
		int healDizzyChance = skill.getIntField("healdizzychance");
		int healStunChance = skill.getIntField("healstunchance");
		int healBlindChance = skill.getIntField("healblindchance");
		int healIntimidateChance = skill.getIntField("healintimidatechance");

		FormupGroupSkill* formup;
		formup = new FormupGroupSkill(skillName, animation, server);
		formup->setCombatSpam(combatSpam);

		formup->setCooldownTime(cooldownTime);
		formup->setHealthCost(healthCost);
		formup->setActionCost(actionCost);
		formup->setMindCost(mindCost);

		formup->setHealDizzyChance(healDizzyChance);
		formup->setHealStunChance(healStunChance);
		formup->setHealBlindChance(healBlindChance);
		formup->setHealIntimidateChance(healIntimidateChance);

		CombatActions->put(formup);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add AddFormupGroupSkill!" << endl;
		return -1;
	}
}

int ScriptAttacksManager::AddRallyGroupSkill(lua_State* L) {
	LuaObject skill(L);

	try {

		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = "";
		String combatSpam = skill.getStringField("combatspam");
		int cooldownTime = skill.getIntField("cooldowntime");
		int healthCost = skill.getIntField("healthcost");
		int actionCost = skill.getIntField("actioncost");
		int mindCost = skill.getIntField("mindcost");
		int rallyDuration = skill.getIntField("rallyduration");
		int accuracyBonus = skill.getIntField("accuracybonus");

		RallyGroupSkill* rally;
		rally = new RallyGroupSkill(skillName, animation, server);
		rally->setCombatSpam(combatSpam);

		rally->setCooldownTime(cooldownTime);
		rally->setHealthCost(healthCost);
		rally->setActionCost(actionCost);
		rally->setMindCost(mindCost);

		rally->setRallyDuration(rallyDuration);
		rally->setAccuracyBonus(accuracyBonus);

		CombatActions->put(rally);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add AddRallyGroupSkill!" << endl;
		return -1;
	}
}

int ScriptAttacksManager::AddRetreatGroupSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	String skillname = skill.getStringField("skillname");
	String combatSpam = skill.getStringField("combatspam");
	int cooldownTime = skill.getIntField("cooldowntime");

	String effect = skill.getStringField("effect");

	int healthCost = skill.getIntField("healthcost");
	int actionCost = skill.getIntField("actioncost");
	int mindCost = skill.getIntField("mindcost");

	bool buffSL = skill.getIntField("buffSL");

	RetreatGroupSkill* retreat = new RetreatGroupSkill(skillname, effect, "", server);

	retreat->setCombatSpam(combatSpam);
	retreat->setCooldownTime(cooldownTime);
	retreat->setHealthCost(healthCost);
	retreat->setActionCost(actionCost);
	retreat->setMindCost(mindCost);
	retreat->setBuffSL(buffSL);

	CombatActions->put(retreat);

	return 0;
}

int ScriptAttacksManager::AddThrowRandomPoolTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ThrowRandomPoolAttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	//cout << attackname << "\n";

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int postureUpStateChance = skill.getIntField("postureUpChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");
	int snareStateChance = skill.getIntField("snareChance");
	int rootStateChance = skill.getIntField("rootChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	String deBuffStrFile = skill.getStringField("deBuffStrFile");
	String deBuffHitMessage = skill.getStringField("deBuffHitMessage");
	String deBuffMissMessage = skill.getStringField("deBuffMissMessage");

	int meleeDefDebuff = skill.getIntField("meleeDefDebuff");
	int rangedDefDebuff = skill.getIntField("rangedDefDebuff");
	int stunDefDebuff = skill.getIntField("stunDefDebuff");
	int intimidateDefDebuff = skill.getIntField("intimidateDefDebuff");

	attack = new ThrowRandomPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setPostureUpChance(postureUpStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);
	attack->setSnareChance(snareStateChance);
	attack->setRootChance(rootStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setDeBuffStrFile(deBuffStrFile);
	attack->setDeBuffHitMessage(deBuffHitMessage);
	attack->setDeBuffMissMessage(deBuffMissMessage);

	attack->setMeleeDefDebuff(meleeDefDebuff);
	attack->setRangedDefDebuff(rangedDefDebuff);
	attack->setStunDefDebuff(stunDefDebuff);
	attack->setIntimidateDefDebuff(intimidateDefDebuff);

	CombatActions->put(attack);

	return 0;
}

int ScriptAttacksManager::AddThrowDirectPoolTargetSkill(lua_State *L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ThrowDirectPoolAttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	//cout << attackname << "\n";

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int healthPoolAttackChance = skill.getIntField("healthAttackChance");
	int strengthPoolAttackChance = skill.getIntField("strengthAttackChance");
	int constitutionPoolAttackChance = skill.getIntField("constitutionAttackChance");

	int actionPoolAttackChance = skill.getIntField("actionAttackChance");
	int quicknessPoolAttackChance = skill.getIntField("quicknessPoolAttackChance");
	int staminaPoolAttackChance = skill.getIntField("staminaPoolAttackChance");

	int mindPoolAttackChance = skill.getIntField("mindAttackChance");
	int focusPoolAttackChance = skill.getIntField("focusAttackChance");
	int willpowerPoolAttackChance = skill.getIntField("willpowerAttackChance");

	int dotType = skill.getIntField("dotType");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");
	int snareStateChance = skill.getIntField("snareChance");
	int rootStateChance = skill.getIntField("rootChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	String deBuffStrFile = skill.getStringField("deBuffStrFile");
	String deBuffHitMessage = skill.getStringField("deBuffHitMessage");
	String deBuffMissMessage = skill.getStringField("deBuffMissMessage");

	int meleeDefDebuff = skill.getIntField("meleeDefDebuff");
	int rangedDefDebuff = skill.getIntField("rangedDefDebuff");
	int stunDefDebuff = skill.getIntField("stunDefDebuff");
	int intimidateDefDebuff = skill.getIntField("intimidateDefDebuff");

	attack = new ThrowDirectPoolAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);

	attack->setHealthPoolAttackRatio(healthPoolAttackChance);
	attack->setStrengthPoolAttackRatio(strengthPoolAttackChance);
	attack->setConstitutionPoolAttackRatio(constitutionPoolAttackChance);

	attack->setActionPoolAttackRatio(actionPoolAttackChance);
	attack->setQuicknessPoolAttackRatio(quicknessPoolAttackChance);
	attack->setStaminaPoolAttackRatio(staminaPoolAttackChance);

	attack->setMindPoolAttackRatio(mindPoolAttackChance);
	attack->setFocusPoolAttackRatio(focusPoolAttackChance);
	attack->setWillpowerPoolAttackRatio(willpowerPoolAttackChance);

	attack->setDotType(dotType);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);
	attack->setSnareChance(snareStateChance);
	attack->setRootChance(rootStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setDeBuffStrFile(deBuffStrFile);
	attack->setDeBuffHitMessage(deBuffHitMessage);
	attack->setDeBuffMissMessage(deBuffMissMessage);

	attack->setMeleeDefDebuff(meleeDefDebuff);
	attack->setRangedDefDebuff(rangedDefDebuff);
	attack->setStunDefDebuff(stunDefDebuff);
	attack->setIntimidateDefDebuff(intimidateDefDebuff);


	CombatActions->put(attack);
	return 0;
}

int ScriptAttacksManager::AddThrowGrenadeTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	ThrowGrenadeAttackTargetSkill* attack;

	String attackname = skill.getStringField("attackname");
	String animation = skill.getStringField("animation");

	//cout << attackname << "\n";

	int weaponType = skill.getIntField("requiredWeaponType");

	int range = skill.getIntField("range");
	float DamageRatio = skill.getFloatField("damageRatio");
	float SpeedRatio = skill.getFloatField("speedRatio");
	int areaRangeDamage = skill.getIntField("areaRange");
	int cone = skill.getIntField("coneAngle");
	int accuracyBonus = skill.getIntField("accuracyBonus");

	int knockdownStateChance = skill.getIntField("knockdownChance");
	int postureDownStateChance = skill.getIntField("postureDownChance");
	int postureUpStateChance = skill.getIntField("postureUpChance");
	int dizzyStateChance = skill.getIntField("dizzyChance");
	int blindStateChance = skill.getIntField("blindChance");
	int stunStateChance = skill.getIntField("stunChance");
	int intimidateStateChance = skill.getIntField("intimidateChance");
	int snareStateChance = skill.getIntField("snareChance");
	int rootStateChance = skill.getIntField("rootChance");

	String CbtSpamBlock = skill.getStringField("CbtSpamBlock");
	String CbtSpamCounter = skill.getStringField("CbtSpamCounter");
	String CbtSpamEvade = skill.getStringField("CbtSpamEvade");
	String CbtSpamHit = skill.getStringField("CbtSpamHit");
	String CbtSpamMiss = skill.getStringField("CbtSpamMiss");

	String deBuffStrFile = skill.getStringField("deBuffStrFile");
	String deBuffHitMessage = skill.getStringField("deBuffHitMessage");
	String deBuffMissMessage = skill.getStringField("deBuffMissMessage");

	int meleeDefDebuff = skill.getIntField("meleeDefDebuff");
	int rangedDefDebuff = skill.getIntField("rangedDefDebuff");
	int stunDefDebuff = skill.getIntField("stunDefDebuff");
	int intimidateDefDebuff = skill.getIntField("intimidateDefDebuff");

	attack = new ThrowGrenadeAttackTargetSkill(attackname, animation, server);

	attack->setRequiredWeaponType(weaponType);
	attack->setRange(range);
	attack->setAreaRangeDamage(areaRangeDamage);
	attack->setConeAngle(cone);
	attack->setDamageRatio(DamageRatio);
	attack->setSpeedRatio(SpeedRatio);
	attack->setAccuracyBonus(accuracyBonus);

	attack->setKnockdownChance(knockdownStateChance);
	attack->setPostureDownChance(postureDownStateChance);
	attack->setPostureUpChance(postureUpStateChance);
	attack->setDizzyChance(dizzyStateChance);
	attack->setBlindChance(blindStateChance);
	attack->setStunChance(stunStateChance);
	attack->setIntimidateChance(intimidateStateChance);
	attack->setSnareChance(snareStateChance);
	attack->setRootChance(rootStateChance);

	attack->setCbtSpamHit(CbtSpamHit);
	attack->setCbtSpamMiss(CbtSpamMiss);
	attack->setCbtSpamEvade(CbtSpamEvade);
	attack->setCbtSpamCounter(CbtSpamCounter);
	attack->setCbtSpamBlock(CbtSpamBlock);

	attack->setDeBuffStrFile(deBuffStrFile);
	attack->setDeBuffHitMessage(deBuffHitMessage);
	attack->setDeBuffMissMessage(deBuffMissMessage);

	attack->setMeleeDefDebuff(meleeDefDebuff);
	attack->setRangedDefDebuff(rangedDefDebuff);
	attack->setStunDefDebuff(stunDefDebuff);
	attack->setIntimidateDefDebuff(intimidateDefDebuff);
	CombatActions->put(attack);

	return 0;
}

int ScriptAttacksManager::AddCMDotAttackTargetSkill(lua_State* L) {
	LuaObject skill(L);

	if (!skill.isValidTable())
		return 0;

	CMDotAttackTargetSkill* dot;

	String skillname = skill.getStringField("skillname");
	String effect = skill.getStringField("effect");
	int medPack = skill.getIntField("medpackType");

	dot = new CMDotAttackTargetSkill(skillname, effect.toCharArray(), server);
	dot->setMedType(medPack);

	CombatActions->put(dot);
	return 0;
}

int ScriptAttacksManager::AddAreaTrackSkill(lua_State* L) {
	LuaObject skill(L);

	try {
		if (!skill.isValidTable())
			return 0;

		String skillName = skill.getStringField("skillname");
		String animation = skill.getStringField("animation");
		int cooldownTime = skill.getIntField("cooldowntime");

		AreaTrackSelfSkill* areaTrack;
		areaTrack = new AreaTrackSelfSkill(skillName, animation, server);

		areaTrack->setCooldownTime(cooldownTime);

		CombatActions->put(areaTrack);
		return 0;
	} catch(...) {
		System::out << "[ERROR] when attempting to add AddAreaTrackSkill!" << endl;
		return -1;
	}
}
