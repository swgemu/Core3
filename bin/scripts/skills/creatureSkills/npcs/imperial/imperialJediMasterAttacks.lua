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

imperialJediMasterAttack1 = {
	attackname = "imperialJediMasterAttack1",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 50,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	--TODO: Find what the bleed attr and value is
	
	CbtSpamBlock = "saberthrow1_block",
	CbtSpamCounter = "saberthrow1_counter",
	CbtSpamEvade = "saberthrow1_evade",
	CbtSpamHit = "saberthrow1_hit",
	CbtSpamMiss = "saberthrow1_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack1)

-----------------------------------------------------------------------

imperialJediMasterAttack2 = {
	attackname = "imperialJediMasterAttack2",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 50,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 35,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberthrow2_block",
	CbtSpamCounter = "saberthrow2_counter",
	CbtSpamEvade = "saberthrow2_evade",
	CbtSpamHit = "saberthrow2_hit",
	CbtSpamMiss = "saberthrow2_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack2)

-----------------------------------------------------------------------

imperialJediMasterAttack3 = {
	attackname = "imperialJediMasterAttack3",
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 32, --30,
	damageRatio = 50,
	speedRatio = 1,
	coneAngle = 40,
	accuracyBonus = 300,
	
	knockdownChance = 40,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	--TODO: Find what the bleed attr and value is
	
	CbtSpamBlock = "saberthrow3_block",
	CbtSpamCounter = "saberthrow3_counter",
	CbtSpamEvade = "saberthrow3_evade",
	CbtSpamHit = "saberthrow3_hit",
	CbtSpamMiss = "saberthrow3_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack3)

-----------------------------------------------------------------------

imperialJediMasterAttack4 = {
	attackname = "imperialJediMasterAttack4",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 300,
	postureDownChance = 10,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 25,
	tickStrengthOfHit = 3, --1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0, --10, ?
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "saberslash1_block",
	CbtSpamCounter = "saberslash1_counter",
	CbtSpamEvade = "saberslash1_evade",
	CbtSpamHit = "saberslash1_hit",
	CbtSpamMiss = "saberslash1_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack4)

-----------------------------------------------------------------------

imperialJediMasterAttack5 = {
	attackname = "imperialJediMasterAttack5",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	areaRange = 0,
	accuracyBonus = 300,
	postureDownChance = 20,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 50,
	tickStrengthOfHit = 3, --1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0, --10, ?
	bleedingType = HEALTH,

	poisonStrength = 0,
	poisonType = 0,

	diseaseStrength = 0,
	diseaseType = 0,
	
	CbtSpamBlock = "saberslash2_block",
	CbtSpamCounter = "saberslash2_counter",
	CbtSpamEvade = "saberslash2_evade",
	CbtSpamHit = "saberslash2_hit",
	CbtSpamMiss = "saberslash2_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack5)

-----------------------------------------------------------------------

imperialJediMasterAttack6 = {
	attackname = "imperialJediMasterAttack6",
	animation = "combo_3b_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 360,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 55,
	blindChance = 55,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmdervish_block",
	CbtSpamCounter = "saberpolearmdervish_counter",
	CbtSpamEvade = "saberpolearmdervish_evade",
	CbtSpamHit = "saberpolearmdervish_hit",
	CbtSpamMiss = "saberpolearmdervish_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack6)

-----------------------------------------------------------------------

imperialJediMasterAttack7 = {
	attackname = "imperialJediMasterAttack7",
	animation = "combo_jedi_2_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 40,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmdervish2_block",
	CbtSpamCounter = "saberpolearmdervish2_counter",
	CbtSpamEvade = "saberpolearmdervish2_evade",
	CbtSpamHit = "saberpolearmdervish2_hit",
	CbtSpamMiss = "saberpolearmdervish2_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack7)

-----------------------------------------------------------------------

imperialJediMasterAttack8 = {
	attackname = "imperialJediMasterAttack8",
	animation = "combo_5a_medium",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 1,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit1_block",
	CbtSpamCounter = "saberpolearmhit1_counter",
	CbtSpamEvade = "saberpolearmhit1_evade",
	CbtSpamHit = "saberpolearmhit1_hit",
	CbtSpamMiss = "saberpolearmhit1_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack8)

-----------------------------------------------------------------------


imperialJediMasterAttack9 = {
	attackname = "imperialJediMasterAttack9",
	animation = "combo_5a_medium",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 1,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit2_block",
	CbtSpamCounter = "saberpolearmhit2_counter",
	CbtSpamEvade = "saberpolearmhit2_evade",
	CbtSpamHit = "saberpolearmhit2_hit",
	CbtSpamMiss = "saberpolearmhit2_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack9)

-----------------------------------------------------------------------

imperialJediMasterAttack10 = {
	attackname = "imperialJediMasterAttack10",
	animation = "combo_4b_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 1,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 55,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmhit3_block",
	CbtSpamCounter = "saberpolearmhit3_counter",
	CbtSpamEvade = "saberpolearmhit3_evade",
	CbtSpamHit = "saberpolearmhit3_hit",
	CbtSpamMiss = "saberpolearmhit3_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack10)

-----------------------------------------------------------------------

imperialJediMasterAttack11 = {
	attackname = "imperialJediMasterAttack11",
	animation = "combo_2e_light",
	
	requiredWeaponType = POLEARMSABER,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	--actionAttackChance = 95,
	actionAttackChance = 45,
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
	
	CbtSpamBlock = "saberpolearmleghit1_block",
	CbtSpamCounter = "saberpolearmleghit1_counter",
	CbtSpamEvade = "saberpolearmleghit1_evade",
	CbtSpamHit = "saberpolearmleghit1_hit",
	CbtSpamMiss = "saberpolearmleghit1_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack11)

-----------------------------------------------------------------------

imperialJediMasterAttack12 = {
	attackname = "imperialJediMasterAttack12",
	animation = "combo_2e_light",
	
	requiredWeaponType = POLEARMSABER,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	--actionAttackChance = 95,
	actionAttackChance = 65,
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
	
	CbtSpamBlock = "saberpolearmleghit2_block",
	CbtSpamCounter = "saberpolearmleghit2_counter",
	CbtSpamEvade = "saberpolearmleghit2_evade",			
	CbtSpamHit = "saberpolearmleghit2_hit",
	CbtSpamMiss = "saberpolearmleghit2_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack12)

-----------------------------------------------------------------------

imperialJediMasterAttack13 = {
	attackname = "imperialJediMasterAttack13",
	animation = "combo_2e_light",
	
	requiredWeaponType = POLEARMSABER,
	
	range = 8,
	damageRatio = 50,
	speedRatio = 1,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 95,
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
	
	CbtSpamBlock = "saberpolearmleghit3_block",
	CbtSpamCounter = "saberpolearmleghit3_counter",
	CbtSpamEvade = "saberpolearmleghit3_evade",
	CbtSpamHit = "saberpolearmleghit3_hit",
	CbtSpamMiss = "saberpolearmleghit3_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack13)

-----------------------------------------------------------------------

imperialJediMasterAttack14 = {
	attackname = "imperialJediMasterAttack14",
	animation = "showoff_1_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 360,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 25,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmspinattack1_block",
	CbtSpamCounter = "saberpolearmspinattack1_counter",
	CbtSpamEvade = "saberpolearmspinattack1_evade",
	CbtSpamHit = "saberpolearmspinattack1_hit",
	CbtSpamMiss = "saberpolearmspinattack1_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack14)

-----------------------------------------------------------------------

imperialJediMasterAttack15 = {
	attackname = "imperialJediMasterAttack15",
	animation = "showoff_1_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 360,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 50,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmspinattack2_block",
	CbtSpamCounter = "saberpolearmspinattack2_counter",
	CbtSpamEvade = "saberpolearmspinattack2_evade",
	CbtSpamHit = "saberpolearmspinattack2_hit",
	CbtSpamMiss = "saberpolearmspinattack2_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack15)

-----------------------------------------------------------------------

imperialJediMasterAttack16 = {
	attackname = "imperialJediMasterAttack16",
	animation = "showoff_1_light",

	requiredWeaponType = POLEARMSABER,

	range = 8,
	coneAngle = 360,
	damageRatio = 50,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 75,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberpolearmspinattack3_block",
	CbtSpamCounter = "saberpolearmspinattack3_counter",
	CbtSpamEvade = "saberpolearmspinattack3_evade",
	CbtSpamHit = "saberpolearmspinattack3_hit",
	CbtSpamMiss = "saberpolearmspinattack3_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediMasterAttack16)
