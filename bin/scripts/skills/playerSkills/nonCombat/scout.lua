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

------------------------------------------------------------------------
ForageSkill = {
	skillName = "forage",
	animation = "forage",       
        actionCost = 50	
}

AddForageSkill(ForageSkill);
------------------------------------------------------------------------

MedicalForageSkill = {
	skillName = "medicalforage",
	animation = "forage",       
        actionCost = 50	
}

AddForageSkill(MedicalForageSkill);
------------------------------------------------------------------------

--------------------------------------------------------------------------

CamoSkill = {
	skillname = "maskscent",
	type = 1,
	duration = 1200.0,	
}

AddCamoSkill(CamoSkill)

----------------------------- Traps NOVICE --------------------------------

--A small dart delivery system, ingeniously crafted from natural organics. The tip is coated with a 
--light Lecepanine poison. This object is thrown at a target in combat. If it hits, the poison will 
--cause the target to become drowsy and slightly confused. This has the effect of making the target 
--dizzy as well as causing a slight decrease in the target's mind and action pools. 
--This weapon cannot kill and only works on animals.

ThrowSkill = { 
	attackname = "throwlecepanindart",
	animation = "throw_trap_drowsy_dart",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
	
	healthAttackChance = 0,
	strengthAttackChance = 0,
	constitutionAttackChance = 0,

	actionAttackChance = 100,
	quicknessAttackChance = 0,
	staminaAttackChance = 0,

	mindAttackChance = 100,
	focusAttackChance = 0,
	willpowerAttackChance = 0,
		
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 100,
	blindChance = 0,
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
	deBuffHitMessage = "trap_drowsy_effect",
	deBuffMissMessage = "trap_drowsy_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowDirectPoolTargetSkill(ThrowSkill)

--A small canister packed with a fine and somewhat sticky mesh. When it strikes the target, 
--the mesh entangles them making movement more difficult. This has the effect of reducing 
--the target's defense against melee attacks.

ThrowSkill = { 
	attackname = "throwwiredmeshtrap",
	animation = "throw_trap_melee_def_1",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 100,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_melee_def_1_effect",
	deBuffMissMessage = "trap_melee_def_1_effect_no",
	
	meleeDefDebuff = -15,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowRandomPoolTargetSkill(ThrowSkill)

----------------------------- Traps TOOLS 1 -------------------------------

--- Similar to the wire mesh trap, but this trap has been enhanced. 
--- The wire mesh has been strengthened and treated with a bioluminescent goo. 
--- The target will become easier to hit with both melee and ranged attacks.


ThrowSkill = { 
	attackname = "throwglowjuicetrap",
	animation = "throw_trap_ranged_def_1",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_melee_ranged_def_1_effect",
	deBuffMissMessage = "trap_melee_ranged_def_1_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = -15,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowRandomPoolTargetSkill(ThrowSkill)

--A spur fashioned from natural organics. A knowledgeable scout can throw this at an enemy creature, 
--placing it in a perfect spot to cause pain. This has the effect of damaging both the creature's 
--health and mind. However, the effects are never fatal.

ThrowSkill = { 
	attackname = "throwsharpbonespur",
	animation = "throw_trap_enraging_spur",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 2.0,
	speedRatio = 2.0,
	areaRange = 0,
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
	dotType = 9,

	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_spur_effect",
	deBuffMissMessage = "trap_spur_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowDirectPoolTargetSkill(ThrowSkill)

----------------------------- Traps TOOLS 2 -------------------------------

--A special device that emits annoying noises. When thrown at a creature by a sufficiently 
--skilled scout, the trap will cause the target to become stunned. The raw shock of the noise 
--will also cause a large amount of damage to the target's mind pool.

ThrowSkill = { 
	attackname = "thrownoisemaker",
	animation = "throw_trap_noise_maker",

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
	blindChance = 0,
	stunChance = 100,
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
	deBuffHitMessage = "trap_noise_maker_effect",
	deBuffMissMessage = "trap_noise_maker_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowDirectPoolTargetSkill(ThrowSkill)

--A small container filled with the natural musk of an animal. The musk has a repellent 
--smell and can cause a target to become distracted. This has the effect of making the 
--target more vulnerable to status effects like stun or intimidate.

ThrowSkill = { 
	attackname = "throwstinkbomb",
	animation = "throw_trap_state_def_1",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_state_def_1_effect",
	deBuffMissMessage = "trap_state_def_1_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = -20,
	intimidateDefDebuff = -20
}

AddThrowRandomPoolTargetSkill(ThrowSkill)

----------------------------- Traps TOOLS 3 -------------------------------

--Similar to the wire mesh trap, but this trap has been enhanced. The wire mesh has been 
--strengthened and treated with a bioluminescent goo. The target will become more vulnerable 
--to both melee and ranged attacks.

ThrowSkill = { 
	attackname = "throwglowwiretrap",
	animation = "throw_trap_melee_ranged_def_1",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_melee_ranged_def_1_effect",
	deBuffMissMessage = "trap_melee_ranged_def_1_effect_no",
	
	meleeDefDebuff = -30,
	rangedDefDebuff = -30,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowRandomPoolTargetSkill(ThrowSkill)

--A small Phecnacine tranquilizer delivery system. This object is thrown at a 
--target in combat. When it strikes something, it releases a thin mist of poison. 
--The poison will cause the target's movement to slow significantly.

ThrowSkill = { 
	attackname = "throwphecnacinedart",
	animation = "throw_trap_tranq_dart",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
			
	knockdownChance = 0,
	postureDownChance = 0,
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 0,
	intimidateChance = 0,
	snareChance = 100,
	rootChance = 0,
	
	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",

	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_tranq_dart_effect",
	deBuffMissMessage = "trap_tranq_dart_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowRandomPoolTargetSkill(ThrowSkill)

----------------------------- Traps TOOLS 4 -------------------------------

--A trap containing some form of compressed mucilage based adhesive. This trap is 
--thrown at a target creature. If the adhesive mesh successfully traps the creature, 
--the target will become immoblie for a short time and will suffer significant 
--damage to its action pool.

ThrowSkill = { 
	attackname = "throwadhesivemesh",
	animation = "throw_trap_webber",

	requiredWeaponType = ALL,
	
	range = 35,
	damageRatio = 1.0,
	speedRatio = 2.0,
	areaRange = 0,
	accuracyBonus = 0,
	
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
	postureUpChance = 0,
	dizzyChance = 0,
	blindChance = 0,
	stunChance = 100,
	intimidateChance = 0,
	snareChance = 0,
	rootChance = 100,
	dotType = 0,

	CbtSpamBlock = "attack_block",
	CbtSpamCounter = "attack_counter",
	CbtSpamEvade = "attack_evade",
	CbtSpamHit = "attack_hit",
	CbtSpamMiss = "attack_miss",
	
	deBuffStrFile = "trap\\trap",
	deBuffHitMessage = "trap_webber_effect",
	deBuffMissMessage = "trap_webber_effect_no",
	
	meleeDefDebuff = 0,
	rangedDefDebuff = 0,
	stunDefDebuff = 0,
	intimidateDefDebuff = 0
}

AddThrowDirectPoolTargetSkill(ThrowSkill)
