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


object_ship_player_player_blacksun_light_s02 = object_ship_player_shared_player_blacksun_light_s02:new {

	name = "player_blacksun_light_s02",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.4553, armor = 299.544,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.21339, armor = 96.52626, speed = 53.26802, pitch = 32.87218, roll = 32.52257, yaw = 32.81568, acceleration = 16.62004, rollRate = 59.35811, pitchRate = 60.43891, deceleration = 8.105305, yawRate = 58.75961,},
	shield_0 = { name = "shd_generic", hitpoints = 387.6872, armor = 497.9937, regen = 4.822149, front = 288.0636, back = 492.3221,},
	armor_0 = { name = "arm_generic", hitpoints = 291.9019, armor = 289.7846,},
	armor_1 = { name = "arm_generic", hitpoints = 299.5869, armor = 287.5455,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.02974, energy = 551.3595,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.22412, armor = 19.69981, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.2314, armor = 199.3554, rate = 0.3375937, drain = 23.52316, maxDamage = 238.7346, shieldEfficiency = 0, minDamage = 117.3354, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_light_s02, "object/ship/player/player_blacksun_light_s02.iff")
