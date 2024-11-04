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


object_ship_droid_fighter_tier2 = object_ship_shared_droid_fighter_tier2:new {
	objectName = "@space/space_mobile_type:droid_fighter_tier2",

	name = "droid_fighter_tier2",
	type = "droid_fighter_tier2",
	faction = "civilian",
	difficulty = "tier2",

	slideFactor = 1.92,
	chassisHitpoints = 600,
	chassisMass = 5000,

	gameObjectType = 536870919,

	reactor = {name = "rct_generic", hitpoints = 450, armor = 450},
	engine = {name = "eng_incom_fusialthrust", hitpoints = 450, armor = 450, speed = 43.26, acceleration = 10.51, deceleration = 8.96, yaw = 18.85, yawRate = 39.55, pitch = 23.79, pitchRate = 47.59, roll = 29.46, rollRate = 53.66},
	shield_0 = {name = "shd_generic", hitpoints = 450, armor = 450, front = 1800, back = 1800, regen = 5.4},
	armor_0 = {name = "arm_generic", hitpoints = 960, armor = 960},
	armor_1 = {name = "arm_generic", hitpoints = 960, armor = 960},
	capacitor = {name = "cap_generic", hitpoints = 450, armor = 450, energy = 5000, rechargeRate = 100},
	weapon_0 = {name = "wpn_incom_blaster", hitpoints = 450, armor = 450, rate = 0.78, drain = 1, maxDamage = 88, minDamage = 63, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier2, "object/ship/droid_fighter_tier2.iff")
