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


object_ship_lambdashuttle_tier5 = object_ship_shared_lambdashuttle_tier5:new {
	objectName = "@space/space_mobile_type:lambdashuttle_tier5",

	name = "lambdashuttle_tier5",
	type = "lambdashuttle_tier5",
	faction = "imperial",
	difficulty = "tier5",

	slideFactor = 1.74,
	chassisHitpoints = 7372.8,
	chassisMass = 5000,

	gameObjectType = 536870919,

	reactor = {name = "rct_generic", hitpoints = 6370.1, armor = 6370.1},
	engine = {name = "eng_incom_fusialthrust", hitpoints = 6370.1, armor = 6370.1, speed = 47.27, acceleration = 11.48, deceleration = 9.79, yaw = 20.6, yawRate = 43.22, pitch = 26, pitchRate = 52, roll = 32.19, rollRate = 58.64},
	shield_0 = {name = "shd_generic", hitpoints = 6370.1, armor = 6370.1, front = 50960.8, back = 50960.8, regen = 46.3},
	armor_0 = {name = "arm_generic", hitpoints = 20384.3, armor = 20384.3},
	armor_1 = {name = "arm_generic", hitpoints = 20384.3, armor = 20384.3},
	capacitor = {name = "cap_generic", hitpoints = 6370.1, armor = 6370.1, energy = 5000, rechargeRate = 100},
	weapon_0 = {name = "wpn_tieadvanced_blaster", hitpoints = 6370.1, armor = 6370.1, rate = 0.78, drain = 1, maxDamage = 576.06, minDamage = 358.68, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_tieadvanced_blaster", hitpoints = 6370.1, armor = 6370.1, rate = 0.78, drain = 1, maxDamage = 576.06, minDamage = 358.68, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier5, "object/ship/lambdashuttle_tier5.iff")
