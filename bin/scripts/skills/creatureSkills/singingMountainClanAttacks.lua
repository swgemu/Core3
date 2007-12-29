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
singingMountainClanAttack1 = {
	attackname = "singingMountainClanAttack1",
	animation = "combo_2d_medium",
	
	requiredWeaponType = POLEARM,

	range = 25,

	damageRatio = 35,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 10,
	postureDownChance = 10,
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

AddRandomPoolAttackTargetSkill(singingMountainClanAttack1)
singingMountainClanAttack2 = {
	attackname = "singingMountainClanAttack2",
	animation = "fire_area_medium",
	
	requiredWeaponType = POLEARM,

	range = 15,

	damageRatio = 20,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
	postureUpChance = 0,
	dizzyChance = 2,
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(singingMountainClanAttack2)
singingMountainClanAttack3 = {
	attackname = "singingMountainClanAttack3",
	animation = "combo_2c_medium",
	
	requiredWeaponType = POLEARM,

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
	blindChance = 10,
	stunChance = 10,
	intimidateChance = 10,
	
	CbtSpamBlock = "",
	CbtSpamCounter = "",
	CbtSpamEvade = "",
	CbtSpamHit = "",
	CbtSpamMiss = "",
}

AddRandomPoolAttackTargetSkill(singingMountainClanAttack3)
singingMountainClanAttack4 = {
	attackname = "singingMountainClanAttack4",
	animation = "combo_2c_medium",
	
	requiredWeaponType = POLEARM,

	range = 15,

	damageRatio = 10,

	speedRatio = 4,
	coneAngle = 30,

	areaRange = 0,
	accuracyBonus = 0,
		
	knockdownChance = 0,
	postureDownChance = 10,
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

AddRandomPoolAttackTargetSkill(singingMountainClanAttack4)


