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


palpatineAttack1 = { 
	attackname = "palpatineAttack1",
	animation = "force_mind_blast_1_particle_level_1_light",
	
	--forceCost = 68,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	stunChance = 50,
	
	CbtSpamBlock = "mindblast1_block",
	CbtSpamCounter = "mindblast1_counter",
	CbtSpamEvade = "mindblast1_evade",
	CbtSpamHit = "mindblast1_hit",
	CbtSpamMiss = "mindblast1_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack1)

-----------------------------------------------------------------------

palpatineAttack2 = { 
	attackname = "palpatineAttack2",
	animation = "force_mind_blast_1_particle_level_1_medium",
	
	--forceCost = 160,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	stunChance = 50,
	
	CbtSpamBlock = "mindblast2_block",
	CbtSpamCounter = "mindblast2_counter",
	CbtSpamEvade = "mindblast2_evade",
	CbtSpamHit = "mindblast2_hit",
	CbtSpamMiss = "mindblast2_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack2)

-----------------------------------------------------------------------

palpatineAttack3 = { 
	attackname = "palpatineAttack3",
	animation = "force_lightning_1_arc_particle_level_5_light",
	
	--forceCost = 125,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 60,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	
	CbtSpamBlock = "forcelightningcone1_block",
	CbtSpamCounter = "forcelightningcone1_counter",
	CbtSpamEvade = "forcelightningcone1_evade",
	CbtSpamHit = "forcelightningcone1_hit",
	CbtSpamMiss = "forcelightningcone1_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack3)

-----------------------------------------------------------------------

palpatineAttack4 = { 
	attackname = "palpatineAttack4",
	animation = "force_lightning_1_arc_particle_level_5_medium",
	
	--forceCost = 250,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 0,
	postureDownChance = 0,
	dizzyChance = 50,
	
	CbtSpamBlock = "forcelightningcone2_block",
	CbtSpamCounter = "forcelightningcone2_counter",
	CbtSpamEvade = "forcelightningcone2_evade",
	CbtSpamHit = "forcelightningcone2_hit",
	CbtSpamMiss = "forcelightningcone2_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack4)

-----------------------------------------------------------------------

palpatineAttack5 = { 
	attackname = "palpatineAttack5",
	animation = "force_lightning_1_particle_level_5_light",
	
	--forceCost = 75,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 0,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	dizzyChance = 50,
	
	CbtSpamBlock = "forcelightningsingle1_block",
	CbtSpamCounter = "forcelightningsingle1_counter",
	CbtSpamEvade = "forcelightningsingle1_evade",
	CbtSpamHit = "forcelightningsingle1_hit",
	CbtSpamMiss = "forcelightningsingle1_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack5)

-----------------------------------------------------------------------

palpatineAttack6 = { 
	attackname = "palpatineAttack6",
	animation = "force_lightning_1_particle_level_5_medium",
	
	--forceCost = 150,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 0,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	dizzyChance = 50,
	
	CbtSpamBlock = "forcelightningsingle2_block",
	CbtSpamCounter = "forcelightningsingle2_counter",
	CbtSpamEvade = "forcelightningsingle2_evade",
	CbtSpamHit = "forcelightningsingle2_hit",
	CbtSpamMiss = "forcelightningsingle2_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack6)

-----------------------------------------------------------------------

palpatineAttack7 = { 
	attackname = "palpatineAttack7",
	animation = "force_knockdown_1_particle_level_1",
	
	--forceCost = 75,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 50,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown1_block",
	CbtSpamCounter = "forceknockdown1_counter",
	CbtSpamEvade = "forceknockdown1_evade",
	CbtSpamHit = "forceknockdown1_hit",
	CbtSpamMiss = "forceknockdown1_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack7)

-----------------------------------------------------------------------

palpatineAttack8 = { 
	attackname = "palpatineAttack8",
	animation = "force_knockdown_1_particle_level_1",
	
	--forceCost = 100,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 50,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown2_block",
	CbtSpamCounter = "forceknockdown2_counter",
	CbtSpamEvade = "forceknockdown2_evade",
	CbtSpamHit = "forceknockdown2_hit",
	CbtSpamMiss = "forceknockdown2_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack8)

-----------------------------------------------------------------------

palpatineAttack9 = { 
	attackname = "palpatineAttack9",
	animation = "force_knockdown_1_arc_particle_level_1",
	
	--forceCost = 200,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	coneAngle = 70,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 50,
	postureDownChance = 0,
	
	CbtSpamBlock = "forceknockdown3_block",
	CbtSpamCounter = "forceknockdown3_counter",
	CbtSpamEvade = "forceknockdown3_evade",
	CbtSpamHit = "forceknockdown3_hit",
	CbtSpamMiss = "forceknockdown3_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack9)

-----------------------------------------------------------------------

palpatineAttack10 = { 
	attackname = "palpatineAttack10",
	animation = "force_choke_1_particle_level_1_medium",
	
	--forceCost = 400,
	
	requiredWeaponType = JEDI,
	
	range = 32,
	damageRatio = 1.2,
	speedRatio = 2.5,
	accuracyBonus = 500,
	
	knockdownChance = 0,
	postureDownChance = 0,
	
	CbtSpamBlock = "forcechoke_block",
	CbtSpamCounter = "forcechoke_counter",
	CbtSpamEvade = "forcechoke_evade",
	CbtSpamHit = "forcechoke_hit",
	CbtSpamMiss = "forcechoke_miss",
	

	invalidStateMask = 0,
	invalidPostures = "",
	instant = 0
}

AddRandomPoolAttackTargetSkill(palpatineAttack10)
