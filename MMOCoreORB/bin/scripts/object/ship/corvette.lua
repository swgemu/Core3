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


object_ship_corvette = object_ship_shared_corvette:new {
	objectName = "@space/space_mobile_type:corvette",

	name = "corvette",
	type = "corvette",
	faction = "rebel",
	difficulty = "",

	slideFactor = 1.76,
	chassisHitpoints = 60000,
	chassisMass = 50000,

	gameObjectType = 536870914,

	reactor = {name = "rct_generic", hitpoints = 10000, armor = 5000},
	engine = {name = "eng_generic", hitpoints = 10000, armor = 5000, speed = 32, acceleration = 8, deceleration = 8, yaw = 3, yawRate = 3, pitch = 3, pitchRate = 3, roll = 3, rollRate = 3},
	shield_0 = {name = "shd_generic", hitpoints = 10000, armor = 5000, front = 20000, back = 20000, regen = 50},
	shield_1 = {name = "shd_generic", hitpoints = 10000, armor = 5000, front = 20000, back = 20000, regen = 40},
	armor_0 = {name = "arm_generic", hitpoints = 15000, armor = 15000},
	armor_1 = {name = "arm_generic", hitpoints = 15000, armor = 15000},
	capacitor = {name = "cap_generic", hitpoints = 10000, armor = 5000, energy = 2356.5, rechargeRate = 128.3},
	bridge = {name = "bdg_generic", hitpoints = 5000, armor = 5000},
	hangar = {name = "hgr_generic", hitpoints = 10000, armor = 10000},
	targeting_station = {name = "tst_generic", hitpoints = 10000, armor = 10000},
	weapon_0 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_2 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_3 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_4 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_5 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_6 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
	weapon_7 = {name = "wpn_corvette_turret_sm_s01", hitpoints = 8000, armor = 4000, rate = 0.471, drain = 43.9, maxDamage = 640, minDamage = 520, shieldEfficiency = 0, armorEfficiency = 0, ammo = 0, ammo_type = 0},
}

ObjectTemplates:addTemplate(object_ship_corvette, "object/ship/corvette.iff")
