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
nightsisterAttack1 = {
	attackname = "nightsisterAttack1",
	--animation = "combo_3a_light",
	animation = "force_choke_1_arc_particle_level_1_light",

	requiredWeaponType = NONE,

	range = 32,

	damageRatio = 55,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack1)
nightsisterAttack2 = {
	attackname = "nightsisterAttack2",
	--animation = "attack_special_hammerfist_light",
	animation = "force_lightning_1_particle_level_5_medium",	

	requiredWeaponType = NONE,

	range = 32,

	damageRatio = 45,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack2)
nightsisterAttack3 = {
	attackname = "nightsisterAttack3",
	--animation = "attack_special_shoulder_bash_medium",
	animation = "force_weaken_1_arc_particle_level_1_medium",

	requiredWeaponType = NONE,

	range = 32,

	damageRatio = 40,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack3)
nightsisterAttack4 = {
	attackname = "nightsisterAttack4",
	--animation = "attack_special_wookiee_slap_light",
	animation = "force_drain_1",

	requiredWeaponType = NONE,

	range = 32,

	damageRatio = 35,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack4)
nightsisterAttack5 = {
	attackname = "nightsisterAttack5",
	--animation = "combo_4b_medium",
	animation = "force_lightning_1_arc_particle_level_1_light",

	requiredWeaponType = NONE,

	range = 32,

	damageRatio = 25,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack5)
nightsisterAttack6 = {
	attackname = "nightsisterAttack6",
	animation = "combo_3d_medium",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 15,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 10,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack6)
nightsisterAttack7 = {
	attackname = "nightsisterAttack7",
	animation = "combo_4a_light",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 15,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 10,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack7)
nightsisterAttack8 = {
	attackname = "nightsisterAttack8",
	animation = "attack_special_shoulder_bash_medium",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 15,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 10,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack8)
nightsisterAttack9 = {
	attackname = "nightsisterAttack9",
	animation = "attack_special_foot_stomp_medium",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 15,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack9)
nightsisterAttack10 = {
	attackname = "nightsisterAttack10",
	animation = "knockdown_unarmed_1",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 15,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack10)
nightsisterAttack11 = {
	attackname = "nightsisterAttack11",
	animation = "combo_5a_medium",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 50,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack11)
nightsisterAttack12 = {
	attackname = "nightsisterAttack12",
	animation = "combo_2c_medium",
	
	requiredWeaponType = NONE,

	range = 15,

	damageRatio = 60,

	speedRatio = 2,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(nightsisterAttack12)
