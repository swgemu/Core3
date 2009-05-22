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

-----------------------------------------------------------------------

--mod values from default speed: 5.376f, default accel: 1.549
-- speed 8.0, accel .999
FR1 = {
	 skillname = "forcerun1",
	 effect = "clienteffect/pl_force_run_self.cef",
	 
	 forceCost = 150, --200,
	 
	 speed = 2.624,
	 acceleration = -.55,
	 slope = 50,
	 duration = 120,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	instant = 0
}

AddForceRunSelfSkill(FR1)

-----------------------------------------------------------------------
-- speed 14.0, accel .999
FR2 = {
	 skillname = "forcerun2",
	 effect = "clienteffect/pl_force_run_self.cef",
	 
	 forceCost = 250, --400,
	 
	 speed = 8.624,
	 acceleration = -.55,
	 slope = 50,
	 duration = 120,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	instant = 0
}
AddForceRunSelfSkill(FR2)


-----------------------------------------------------------------------
-- speed 20.0, accel .999
FR3 = {
	 skillname = "forcerun3",
	 effect = "clienteffect/pl_force_run_self.cef",
	 
	 forceCost = 350, --600,
	 
	 speed = 14.624,
	 acceleration = -.55,
	 slope = 50,
	 duration = 120,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	instant = 0
}
AddForceRunSelfSkill(FR3)

-----------------------------------------------------------------------

ForceSpeed1 = {
	skillname = "forcespeed1",
	effect = "clienteffect/pl_force_speed_self.cef",
	
	forceCost = 150,
	
	duration = 180,
	
	speedBonus = 15,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	instant = 0
}

AddForceSpeedSelfSkill(ForceSpeed1)

-----------------------------------------------------------------------

ForceSpeed2 = {
	skillname = "forcespeed2",
	effect = "clienteffect/pl_force_speed_self.cef",
	
	forceCost = 300,
	
	duration = 360,
	
	speedBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	instant = 0
}

AddForceSpeedSelfSkill(ForceSpeed2)

-----------------------------------------------------------------------

ForceResistBleeding = {
	skillname = "forceresistbleeding",
	effect = "clienteffect/pl_force_resist_bleeding_self.cef",
	
	forceCost = 250,
	
	duration = 800,
	
	rBBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddForceResistBleedingSelfSkill(ForceResistBleeding)

-----------------------------------------------------------------------

ForceResistPoison = {
	skillname = "forceresistpoison",
	effect = "clienteffect/pl_force_resist_poison_self.cef",
	
	forceCost = 250,
	
	duration = 900,
	
	rPBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddForceResistPoisonSelfSkill(ForceResistPoison)

-----------------------------------------------------------------------

ForceResistDisease = {
	skillname = "forceresistdisease",
	effect = "clienteffect/pl_force_resist_disease_self.cef",
	
	forceCost = 250,
	
	duration = 900,
	
	rDBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddForceResistDiseaseSelfSkill(ForceResistDisease)

-----------------------------------------------------------------------

ForceResistStates = {
	skillname = "forceresiststates",
	effect = "clienteffect/pl_force_resist_states_self.cef",
	
	forceCost = 250,
	
	duration = 900,
	
	rSBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}

AddForceResistStatesSelfSkill(ForceResistStates)

-----------------------------------------------------------------------

ForceMeditate = {
	skillname = "forcemeditate",
	effectname = "forcemeditate",

	--regen = "300",
	regen = "*3",

        invalidStateMask = 4164812873, --cover, aiming, feigndeath, frozen, swimming, sittingOnChair, crafting, glowingJedi, ridingMount, mountedCreature, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "0,3,1,2,5,6,7,9,10,11,12,13,14,4,",

	instant = 0
}

AddForceMeditateSelfSkill(ForceMeditate)

-----------------------------------------------------------------------

DrainForce = {
	
	skillname = "drainforce",
	effectname = "force_drain_1",
	
	--forceCost = 0,
	speedRatio = 4,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,12,13,14,",
	
	instant = 0
}
--AddDrainForceSkill(DrainForce)

-----------------------------------------------------------------------

ForceArmor1 = {
	skillname = "forcearmor1",
	effect = "clienteffect/pl_force_arnir_self.cef",
	
	forceCost = 75,
	
	duration = 900,
	
	armorBonus = 25,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,13,14,",
	instant = 0
}

AddForceArmor2SelfSkill(ForceArmor1)

-----------------------------------------------------------------------

ForceArmor2 = {
	skillname = "forcearmor2",
	effect = "clienteffect/pl_force_armor_self.cef",
	
	forceCost = 150,
	
	duration = 1800,
	
	armorBonus = 45,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,13,14,",
	instant = 0
}

AddForceArmor2SelfSkill(ForceArmor2)

-----------------------------------------------------------------------

HealEnhanceSkill = {
	skillname = "forceshield1",
	effect = "clienteffect/pl_force_shield_self.cef",
	
	forceCost = 75,
	
	duration = 15.0,
	
	speed = 1.0, --.25,? -- needs to be set to the ratio of 25%
	
	healthBonus = 0,
	actionBonus = 0,
	mindBonus = 0,
	
	damageBonus = 0,
	accuracyBonus = 0,
	
	defenseBonus = 25,
	speedBonus = 0,
	
	StartFlyText = "",
	FinishFlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,13,14,",
	instant = 0
}

AddEnhanceSelfSkill(HealEnhanceSkill)

-----------------------------------------------------------------------

HealEnhanceSkill = {
	skillname = "forceshield2",
	effect = "clienteffect/pl_force_shield_self.cef",
	
	forceCost = 150,
	
	duration = 30.0,
	
	speed = 1.0, --.45,? -- needs to be set to the ratio of 45%

	healthBonus = 0,
	actionBonus = 0,
	mindBonus = 0,

	damageBonus = 0,
	accuracyBonus = 0,

	defenseBonus = 45,
	speedBonus = 0,
	
	StartFlyText = "",
	
	FinishFlyText = "",

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,7,8,9,10,11,13,14,",
	instant = 0
}

AddEnhanceSelfSkill(HealEnhanceSkill)

-----------------------------------------------------------------------
