--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.
RandPoolAtt = {
	attackname = "unarmedhit2",
	animation = "combo_3a_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 2.5,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "unarmed_dam2_block",
	CbtSpamCounter = "unarmed_dam2_counter",
	CbtSpamEvade = "unarmed_dam2_evade",
	CbtSpamHit = "unarmed_dam2_hit",
	CbtSpamMiss = "unarmed_dam2_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------------------------------------

skill = {
	skillname = "meditate",
	effectname = "",

        invalidStateMask = 4164812873, --cover, aiming, feigndeath, frozen, swimming, sittingOnChair, crafting, glowingJedi, ridingMount, mountedCreature, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "0,3,1,2,5,6,7,9,10,11,12,13,14,4,",
	instant = 0
}

AddMeditateSkill(skill)

-------------------------------------------------------------

powerboost = {
 	skillname = "powerboost",
 	effect = "",
 	bonus = 0.5, --multiple of base mind to add to HAM  

        invalidStateMask = 3963615211, --cover, combat, aiming, berzerk, feigndeath, combatAttitudeEvasive, combatAttitudeNormal, combatAttitudeAggressive, tumbling, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, sittingOnChair, crafting, glowingJedi, onFire, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "0,3,1,2,5,6,7,9,10,11,12,13,14,4,",	
	instant = 0
}
 
AddPowerboostSkill(powerboost)

-------------------------------------------------------------

RandPoolAtt = {
	attackname = "unarmedknockdown1",
	animation = "attack_special_shoulder_bash_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 1.0,
	speedRatio = 1.5,
	areaRange = 0,
	accuracyBonus = 0,
	intimidateChance = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 15,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------------------------------------

RandPoolAtt = {
	attackname = "unarmedknockdown2",
	animation = "attack_special_hammerfist_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 40,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------------------------------------

RandPoolAtt = {
	attackname = "unarmeddizzy1",
	animation = "attack_special_wookiee_slap_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 1.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 25,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "unarmed_dizzy_block",
	CbtSpamCounter = "unarmed_dizzy_counter",
	CbtSpamEvade = "unarmed_dizzy_evade",
	CbtSpamHit = "unarmed_dizzy_hit",
	CbtSpamMiss = "unarmed_dizzy_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------------------------------------

DirectPoolAtt = {
	attackname = "unarmedcombo1",
	animation = "combo_4b_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	healthAttackChance = 100,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 10,
	focusAttackChance = 0,
	willpowerAttackChance = 0,	

	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-------------------------------------------------------------

RandPoolAtt = {
	attackname = "unarmedspinattack2",
	animation = "combo_3d_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 3.0,
	areaRange = 7,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-------------------------------------------------------------

DirectPoolAtt = {
	attackname = "unarmedcombo2",
	animation = "combo_4a_light",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 3.0,
	speedRatio = 4.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
		
	healthAttackChance = 100,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 20,
	focusAttackChance = 0,
	willpowerAttackChance = 0,	

	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

-------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "unarmedbodyhit1",
	animation = "attack_special_shoulder_bash_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 100,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

----------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "unarmedleghit1",
	animation = "attack_special_foot_stomp_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 0,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

----------------------------------------------------------------

DirectPoolAtt = { 
	attackname = "unarmedheadhit1",
	animation = "knockdown_unarmed_1",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 2.5,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,

	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 0,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,
	
	mindAttackChance = 100,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddDirectPoolAttackTargetSkill(DirectPoolAtt)

----------------------------------------------------------------

RandPoolAtt = {
	attackname = "unarmedhit3",
	animation = "combo_5a_medium",

	requiredWeaponType = UNARMED,
	
	range = 0,
	damageRatio = 4.0,
	speedRatio = 3.0,
	areaRange = 0,
	accuracyBonus = 0,

	healthCostMultiplier = 1,
	actionCostMultiplier = 1,
	mindCostMultiplier = 1,
	forceCostMultiplier = 0,
	
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 40,
	stunChance = 0,
	intimidateChance = 0,
	CbtSpamBlock = "melee_block",
	CbtSpamCounter = "melee_counter",
	CbtSpamEvade = "melee_evade",
	CbtSpamHit = "melee_hit",
	CbtSpamMiss = "melee_miss",

        invalidStateMask = 3894805552, --alert, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}

AddRandomPoolAttackTargetSkill(RandPoolAtt)

-----------------------------------------------------------
