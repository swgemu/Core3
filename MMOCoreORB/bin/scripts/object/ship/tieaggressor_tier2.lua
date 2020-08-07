--Copyright (C) 2010 <SWGEmu>


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


object_ship_tieaggressor_tier2 = object_ship_shared_tieaggressor_tier2:new {

	name = "tieaggressor_tier2",
	slideFactor = 1.68,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 440.7177, armor = 434.8118,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 443.6325, armor = 441.8808, speed = 41.36641, pitch = 22.77368, roll = 28.52988, yaw = 18.10229, acceleration = 10.16602, rollRate = 51.90778, pitchRate = 47.57179, deceleration = 8.690198, yawRate = 38.85206,},
	shield_0 = { name = "shd_generic", hitpoints = 442.1943, armor = 435.0421, regen = 5.209555, front = 1777.746, back = 1719.549,},
	armor_0 = { name = "arm_generic", hitpoints = 919.3343, armor = 915.1345,},
	armor_1 = { name = "arm_generic", hitpoints = 936.4276, armor = 923.0693,},
	capacitor = { name = "cap_generic", hitpoints = 446.9101, armor = 447.7964, rechargeRate = 97.19183, energy = 4998.832,},
	weapon_0 = { name = "wpn_generic", hitpoints = 441.1465, armor = 441.8784, rate = 0.7538269, drain = 0.9854959, maxDamage = 96.29839, shieldEfficiency = 0.5356515, minDamage = 67.84282, ammo = 0, ammo_type = 0, armorEfficiency = 0.5545893,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 432.3766, armor = 442.9016, rate = 0.7650806, drain = 0.9759557, maxDamage = 93.98589, shieldEfficiency = 0.5574797, minDamage = 68.49976, ammo = 0, ammo_type = 0, armorEfficiency = 0.5368531,},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor_tier2, "object/ship/tieaggressor_tier2.iff")
