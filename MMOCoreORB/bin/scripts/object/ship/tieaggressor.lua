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


object_ship_tieaggressor = object_ship_shared_tieaggressor:new {
	objectName = "@space/space_mobile_type:tieaggressor",

	name = "tieaggressor",
	type = "tieaggressor",
	faction = "imperial",
	difficulty = "",

	slideFactor = 1.78,
	chassisHitpoints = 322,
	chassisMass = 10000,

	gameObjectType = 536870919,

	reactor = {name = "rct_generic", hitpoints = 100, armor = 200},
	engine = {name = "eng_qualdex_kyromaster", hitpoints = 100, armor = 200, speed = 46, acceleration = 12.5, deceleration = 6.25, yaw = 18.3, yawRate = 42.1, pitch = 18.3, pitchRate = 42.1, roll = 18.3, rollRate = 42.1},
	shield_0 = {name = "shd_generic", hitpoints = 200, armor = 200, front = 500, back = 800, regen = 5},
	armor_0 = {name = "arm_generic", hitpoints = 600, armor = 600},
	armor_1 = {name = "arm_generic", hitpoints = 600, armor = 600},
	capacitor = {name = "cap_generic", hitpoints = 100, armor = 200, energy = 1468.8, rechargeRate = 58.752},
	weapon_0 = {name = "wpn_generic", hitpoints = 200, armor = 200, rate = 0.573, drain = 27.648, maxDamage = 360, minDamage = 240, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 200, armor = 200, rate = 4, drain = 27.648, maxDamage = 27.648, minDamage = 27.648, shieldEfficiency = 0, armorEfficiency = 0, ammo = 50, ammo_type = 3},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor, "object/ship/tieaggressor.iff")
