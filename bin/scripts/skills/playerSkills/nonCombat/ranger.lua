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

CamoSkill = {
	skillname = "conceal",
	type = 2,
	duration = 3600.0
}

AddCamoSkill(CamoSkill);

----------------------------- Advanced Trapping 2 -------------------------------

--- A small bomb that emits a bright flash on impact.  
--- This flash is intense enough to blind most creatures for a short amount of time. 
--- The flash bomb bursts, blinding nearby enemies! 

ThrowSkill = { 
	attackname = "throwflashbomb",
	animation = "throw_trap_flash_bomb",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 2.0,
	speedRatio = 2.0,
	areaRange = 4,
	accuracyBonus = 0,
	
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
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 100,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	dotType = 0,

	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_flash_bomb_effect",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowDirectPoolTargetSkill(ThrowSkill);

----------------------------- Advanced Trapping 3 -------------------------------

--- The sonic pulse is a small bomb activated by impact.  
--- When triggered, it emits an extremely powerful pulse of sonic energy.
--- This has the result of stunning and dizzying any creatures caught within its effective radius.

ThrowSkill = { 
	attackname = "throwsonicpulse",
	animation = "throw_trap_sonic_pulse",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 8,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 100,
	blindChance = 0,
	stunChance = 100,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_sonic_pulse_effect",
	deBuffMissMessage = "",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowRandomPoolTargetSkill(ThrowSkill);
----------------------------------------------------------------

AreaTrackSkill = {
	skillname = "areatrack",
	animation = "combarea",
	cooldowntime = 30
}

AddAreaTrackSkill(AreaTrackSkill);