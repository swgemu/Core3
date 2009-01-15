--Copyright (C) 2008 <SWGEmu>
 
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

kimogilaAttack1 = {
        attackname = "kimogilaAttack1",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 80,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack1)

----------------------------------------------------------

-- combo
kimogilaAttack2 = {
        attackname = "kimogilaAttack2",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 90,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 90,
        blindChance = 0,
        stunChance = 90,
        intimidateChance = 90,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack2)

----------------------------------------------------------

kimogilaAttack3 = {
        attackname = "kimogilaAttack3",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack3)

----------------------------------------------------------

kimogilaAttack4 = {
        attackname = "kimogilaAttack4",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 80,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack4)

----------------------------------------------------------

kimogilaAttack5 = {
        attackname = "kimogilaAttack5",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack5)

----------------------------------------------------------

kimogilaAttack6 = {
        attackname = "kimogilaAttack6",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack6)

----------------------------------------------------------

kimogilaAttack7 = {
        attackname = "kimogilaAttack7",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,

        healthAttackChance = 50,
        actionAttackChance = 0,
        mindAttackChance = 0,

        dotChance = 90,
        tickStrengthOfHit = 1,

        fireStrength = 0,
        fireType = 0,

        bleedingStrength = 0,
	bleedingType = 0,

        poisonStrength = 0,
        poisonType = 0,

        diseaseStrength = 0,
        diseaseType = HEALTH,
                
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddDotPoolAttackTargetSkill(kimogilaAttack7)

----------------------------------------------------------------------------

kimogilaAttack8 = {
        attackname = "kimogilaAttack8",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 0,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 50,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack8)

----------------------------------------------------------

kimogilaAttack9 = {
        attackname = "kimogilaAttack9",
        animation = "creature_attack_medium",
        
        requiredWeaponType = MELEE,

        range = 14,

        damageRatio = 1.2,

        speedRatio = 2,

        arearange = 14,
        accuracyBonus = 0,
                
        knockdownChance = 0,
        postureDownChance = 50,
        postureUpChance = 0,
        dizzyChance = 0,
        blindChance = 0,
        stunChance = 0,
        intimidateChance = 0,
        
        CbtSpamBlock = "attack_block",
        CbtSpamCounter = "attack_counter",
        CbtSpamEvade = "attack_evade",
        CbtSpamHit = "attack_hit",
        CbtSpamMiss = "attack_miss",
}

AddRandomPoolAttackTargetSkill(kimogilaAttack9)