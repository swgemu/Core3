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

-- Player skills
ForceHealSk = {
	skillname = "healallself2",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 400,
	HealHealth = 1500,
	HealAction = 1500,
	HealMind = 1500,

	speed = 4.0,

	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healstatesself",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 50,
	HealHealth = 0,
	HealAction = 0,
	HealMind = 0,

	speed = 1.0,

	healDizzy = 1,
	healStun = 1,
	healBlind = 1,
	healIntimidate = 1,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "saberpolearmdervish2",
	animation = "combo_jedi_2_light",

	requiredWeaponType = JEDI,

	range = 5,
	coneAngle = 40,
	damageRatio = 2.5,
	speedRatio = 1.5,
	accuracyBonus = 0,
	
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

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

ForceRandomPoolAtt = {
	attackname = "saberthrow3",
	animation = "saberthrow_posture_change",

	requiredWeaponType = JEDI,

	range = 32,
	damageRatio = 2.0,
	speedRatio = 1.0,
	coneAngle = 40,
	accuracyBonus = 0,
	
	knockdownChance = 40,
	postureDownChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,

	CbtSpamBlock = "saberthrow3_block",
	CbtSpamCounter = "saberthrow3_counter",
	CbtSpamEvade = "saberthrow3_evade",
	CbtSpamHit = "saberthrow3_hit",
	CbtSpamMiss = "saberthrow3_miss"
}

AddForceRandomPoolAttackTargetSkill(ForceRandomPoolAtt)

-----------------------------------------------------------------------

DotPoolAtt = { 
	attackname = "saberslash2",
	animation = "combo_2d_light",

	requiredWeaponType = JEDI,
	
	range = 5,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
	postureDownChance = 20,
		
	healthAttackChance = 50,
	actionAttackChance = 35,
	mindAttackChance = 15,

	dotChance = 50,
	tickStrengthOfHit = 1,

	fireStrength = 0,
	fireType = 0,

	bleedingStrength = 0,
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

AddForceDotPoolAttackTargetSkill(DotPoolAtt)

-----------------------------------------------------------------------
