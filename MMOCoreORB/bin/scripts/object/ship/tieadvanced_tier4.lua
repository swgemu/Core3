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


object_ship_tieadvanced_tier4 = object_ship_shared_tieadvanced_tier4:new {

	name = "tieadvanced_tier4",
	slideFactor = 1.76,
	chassisHitpoints = 2304,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2383.936, armor = 2372.83,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 2454.34, armor = 2462.397, speed = 43.90972, pitch = 24.47938, roll = 30.09903, yaw = 19.61928, acceleration = 10.94836, rollRate = 55.69075, pitchRate = 48.46919, deceleration = 9.12324, yawRate = 40.21594,},
	shield_0 = { name = "shd_generic", hitpoints = 2481.644, armor = 2380.431, regen = 17.79446, front = 9762.949, back = 9540.177,},
	armor_0 = { name = "arm_generic", hitpoints = 5238.872, armor = 5060.255,},
	armor_1 = { name = "arm_generic", hitpoints = 5229.106, armor = 5228.5,},
	capacitor = { name = "cap_generic", hitpoints = 2397.354, armor = 2436.647, rechargeRate = 95.14581, energy = 4903.538,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 2382.046, armor = 2453.774, rate = 0.7498173, drain = 0.9899317, maxDamage = 301.9972, shieldEfficiency = 0.5585793, minDamage = 194.021, ammo = 0, ammo_type = 0, armorEfficiency = 0.5374274,},
}

ObjectTemplates:addTemplate(object_ship_tieadvanced_tier4, "object/ship/tieadvanced_tier4.iff")
