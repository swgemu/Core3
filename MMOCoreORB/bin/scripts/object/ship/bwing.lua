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


object_ship_bwing = object_ship_shared_bwing:new {
	objectName = "@space/space_mobile_type:bwing",

	name = "bwing",
	type = "bwing",
	faction = "rebel",
	difficulty = "",

	slideFactor = 1.76,
	chassisHitpoints = 300,
	chassisMass = 10000,

	gameObjectType = 536870919,

	reactor = {name = "rct_generic", hitpoints = 100, armor = 200},
	engine = {name = "eng_incom_fusialthrust", hitpoints = 100, armor = 200, speed = 48, acceleration = 16.2, deceleration = 8.1, yaw = 22.3, yawRate = 52.7, pitch = 22.3, pitchRate = 52.7, roll = 22.3, rollRate = 52.7},
	shield_0 = {name = "shd_generic", hitpoints = 200, armor = 200, front = 600, back = 700, regen = 5},
	armor_0 = {name = "arm_generic", hitpoints = 800, armor = 800},
	armor_1 = {name = "arm_generic", hitpoints = 800, armor = 800},
	capacitor = {name = "cap_generic", hitpoints = 100, armor = 200, energy = 1740.8, rechargeRate = 69.632},
	weapon_0 = {name = "wpn_bwing_blaster", hitpoints = 200, armor = 200, rate = 0.679, drain = 32.768, maxDamage = 310, minDamage = 200, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_bwing_blaster", hitpoints = 200, armor = 200, rate = 0.679, drain = 32.768, maxDamage = 32.768, minDamage = 32.768, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_2 = {name = "wpn_bwing_blaster", hitpoints = 100, armor = 200, rate = 0.679, drain = 32.768, maxDamage = 32.768, minDamage = 32.768, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_3 = {name = "wpn_bwing_blaster", hitpoints = 100, armor = 200, rate = 0.679, drain = 32.768, maxDamage = 32.768, minDamage = 32.768, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
}

ObjectTemplates:addTemplate(object_ship_bwing, "object/ship/bwing.iff")
