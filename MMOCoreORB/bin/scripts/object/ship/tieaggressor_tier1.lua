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


object_ship_tieaggressor_tier1 = object_ship_shared_tieaggressor_tier1:new {

	name = "tieaggressor_tier1",
	slideFactor = 1.68,
	chassisHitpoints = 240,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 143.0673, armor = 144.3153,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 142.5576, armor = 149.864, speed = 40.16462, pitch = 22.03855, roll = 28.24532, yaw = 17.72132, acceleration = 10.108, rollRate = 50.61727, pitchRate = 44.66624, deceleration = 8.380624, yawRate = 37.57921,},
	shield_0 = { name = "shd_generic", hitpoints = 147.6856, armor = 146.1448, regen = 2.887932, front = 592.2103, back = 598.0905,},
	armor_0 = { name = "arm_generic", hitpoints = 307.0391, armor = 310.4557,},
	armor_1 = { name = "arm_generic", hitpoints = 309.5951, armor = 309.4789,},
	capacitor = { name = "cap_generic", hitpoints = 144.1117, armor = 147.155, rechargeRate = 95.16724, energy = 4857.753,},
	weapon_0 = { name = "wpn_generic", hitpoints = 143.6016, armor = 146.9388, rate = 0.7445738, drain = 0.9558452, maxDamage = 42.98059, shieldEfficiency = 0.5375353, minDamage = 32.66764, ammo = 0, ammo_type = 0, armorEfficiency = 0.5468831,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 146.8454, armor = 148.7122, rate = 0.74757, drain = 0.967422, maxDamage = 43.86717, shieldEfficiency = 0.5392042, minDamage = 31.73483, ammo = 0, ammo_type = 0, armorEfficiency = 0.5415295,},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor_tier1, "object/ship/tieaggressor_tier1.iff")
