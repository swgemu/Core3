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

imperialJediKnightAttack1 = {
	attackname = "imperialJediKnightAttack1",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 1.2,
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

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack1)

-----------------------------------------------------------------------

imperialJediKnightAttack2 = {
	attackname = "imperialJediKnightAttack2",
	animation = "saberthrow_posture_change",
	
	requiredWeaponType = JEDI,
	
	range = 32, --30,
	damageRatio = 1.2,
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

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack2)

-----------------------------------------------------------------------

imperialJediKnightAttack3 = {
	attackname = "imperialJediKnightAttack3",
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 32, --30,
	damageRatio = 1.2,
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

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack3)

-----------------------------------------------------------------------

imperialJediKnightAttack4 = {
	attackname = "imperialJediKnightAttack4",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 1.2,
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

	bleedingStrength = 3, --10, ?
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

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack4)

-----------------------------------------------------------------------

imperialJediKnightAttack5 = {
	attackname = "imperialJediKnightAttack5",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 8,
	damageRatio = 1.2,
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

	bleedingStrength = 3, --10, ?
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

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack5)

----------------------------------------------------------------------

imperialJediKnightAttack6 = {
	attackname = "imperialJediKnightAttack6",
	animation = "combo_jedi_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	coneAngel = 40,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	blindChance = 45,
	stunChance = 40,
	intimidateChance = 0,
	
	CbtSpamBlock = "saber2hphantom_block",
	CbtSpamCounter = "saber2hphantom_counter",
	CbtSpamEvade = "saber2hphantom_evade",
	CbtSpamHit = "saber2hphantom_hit",
	CbtSpamMiss = "saber2hphantom_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack6)
-----------------------------------------------------------------------

imperialJediKnightAttack7 = {
	attackname = "imperialJediKnightAttack7",
	animation = "combo_3a_medium",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 40,
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
	
	CbtSpamBlock = "saber2hbodyhit1_block",
	CbtSpamCounter = "saber2hbodyhit1_counter",
	CbtSpamEvade = "saber2hbodyhit1_evade",
	CbtSpamHit = "saber2hbodyhit1_hit",
	CbtSpamMiss = "saber2hbodyhit1_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack7)

-----------------------------------------------------------------------

imperialJediKnightAttack8 = {
	attackname = "imperialJediKnightAttack8",
	animation = "combo_3b_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 50,
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
	
	CbtSpamBlock = "saber2hbodyhit2_block",
	CbtSpamCounter = "saber2hbodyhit2_counter",
	CbtSpamEvade = "saber2hbodyhit2_evade",
	CbtSpamHit = "saber2hbodyhit2_hit",
	CbtSpamMiss = "saber2hbodyhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack8)
	
-----------------------------------------------------------------------

imperialJediKnightAttack9 = {
	attackname = "imperialJediKnightAttack9",
	animation = "showoff_3_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	
	healthAttackChance = 80,
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
	
	CbtSpamBlock = "saber2hbodyhit3_block",
	CbtSpamCounter = "saber2hbodyhit3_counter",
	CbtSpamEvade = "saber2hbodyhit3_evade",
	CbtSpamHit = "saber2hbodyhit3_hit",
	CbtSpamMiss = "saber2hbodyhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack9)

-----------------------------------------------------------------------

imperialJediKnightAttack10 = {
	attackname = "imperialJediKnightAttack10",
	animation = "combo_2a_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 15,
	
	CbtSpamBlock = "saber2hsweep1_block",
	CbtSpamCounter = "saber2hsweep1_counter",
	CbtSpamEvade = "saber2hsweep1_evade",
	CbtSpamHit = "saber2hsweep1_hit",
	CbtSpamMiss = "saber2hsweep1_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack10)

-----------------------------------------------------------------------

imperialJediKnightAttack11 = {
	attackname = "imperialJediKnightAttack11",
	animation = "combo_3d_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 30,
	
	CbtSpamBlock = "saber2hsweep2_block",
	CbtSpamCounter = "saber2hsweep2_counter",
	CbtSpamEvade = "saber2hsweep2_evade",
	CbtSpamHit = "saber2hsweep2_hit",
	CbtSpamMiss = "saber2hsweep2_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack11)

-----------------------------------------------------------------------

imperialJediKnightAttack12 = {
	attackname = "imperialJediKnightAttack12",
	animation = "showoff_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 45,
	
	CbtSpamBlock = "saber2hsweep3_block",
	CbtSpamCounter = "saber2hsweep3_counter",
	CbtSpamEvade = "saber2hsweep3_evade",
	CbtSpamHit = "saber2hsweep3_hit",
	CbtSpamMiss = "saber2hsweep3_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack12)

-----------------------------------------------------------------------

imperialJediKnightAttack13 = {
	attackname = "imperialJediKnightAttack13",
	animation = "combo_2a_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit1_block",
	CbtSpamCounter = "saber2hhit1_counter",
	CbtSpamEvade = "saber2hhit1_evade",
	CbtSpamHit = "saber2hhit1_hit",
	CbtSpamMiss = "saber2hhit1_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack13)

-----------------------------------------------------------------------

imperialJediKnightAttack14 = {
	attackname = "imperialJediKnightAttack14",
	animation = "combo_2b_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit2_block",
	CbtSpamCounter = "saber2hhit2_counter",
	CbtSpamEvade = "saber2hhit2_evade",
	CbtSpamHit = "saber2hhit2_hit",
	CbtSpamMiss = "saber2hhit2_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack14)

-----------------------------------------------------------------------

imperialJediKnightAttack15 = {
	attackname = "imperialJediKnightAttack15",
	animation = "showoff_2_light",
	
	requiredWeaponType = TWOHANDSABER,
	
	range = 8,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "saber2hhit3_block",
	CbtSpamCounter = "saber2hhit3_counter",
	CbtSpamEvade = "saber2hhit3_evade",
	CbtSpamHit = "saber2hhit3_hit",
	CbtSpamMiss = "saber2hhit3_miss"
	
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack15)

-----------------------------------------------------------------------

imperialJediKnightAttack16 = {
	attackname = "imperialJediKnightAttack16",
	animation = "showoff_2_light",

	requiredWeaponType = TWOHANDSABER,

	range = 8,
	coneAngle = 360,
	damageRatio = 1.2,
	speedRatio = 1,
	accuracyBonus = 300,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 25,
	blindChance = 25,
	stunChance = 25,
	intimidateChance = 0,

	CbtSpamBlock = "saber2hfrenzy_block",
	CbtSpamCounter = "saber2hfrenzy_counter",
	CbtSpamEvade = "saber2hfrenzy_evade",
	CbtSpamHit = "saber2hfrenzy_hit",
	CbtSpamMiss = "saber2hfrenzy_miss"
}

AddRandomPoolAttackTargetSkill(imperialJediKnightAttack16)
