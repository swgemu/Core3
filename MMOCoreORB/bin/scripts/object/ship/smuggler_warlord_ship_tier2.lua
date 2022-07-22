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


object_ship_smuggler_warlord_ship_tier2 = object_ship_shared_smuggler_warlord_ship_tier2:new {

	name = "smuggler_warlord_ship_tier2",
	slideFactor = 1.76,
	chassisHitpoints = 6000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4321.826, armor = 4451.239,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4429.303, armor = 4295.924, speed = 43.14472, pitch = 23.08634, roll = 29.4404, yaw = 18.04314, acceleration = 10.12215, rollRate = 52.10101, pitchRate = 46.79858, deceleration = 8.719544, yawRate = 39.04117,},
	shield_0 = { name = "shd_generic", hitpoints = 4288.418, armor = 4343.791, regen = 7.772818, front = 17562.24, back = 17252.73,},
	armor_0 = { name = "arm_generic", hitpoints = 9289.013, armor = 9553.75,},
	armor_1 = { name = "arm_generic", hitpoints = 9388.58, armor = 9220.634,},
	capacitor = { name = "cap_generic", hitpoints = 4422.932, armor = 4312.105, rechargeRate = 98.33199, energy = 4922.378,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 4305.047, armor = 4375.163, rate = 0.7766976, drain = 0.9913002, maxDamage = 215.799, shieldEfficiency = 0.5378641, minDamage = 154.8787, ammo = 0, ammo_type = 0, armorEfficiency = 0.5591386,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 4484.238, armor = 4418.232, rate = 0.7457786, drain = 0.9655387, maxDamage = 217.3993, shieldEfficiency = 0.5431234, minDamage = 151.0184, ammo = 0, ammo_type = 0, armorEfficiency = 0.5544425,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 4300.5, armor = 4452.165, rate = 0.7740941, drain = 0.9931435, maxDamage = 218.8925, shieldEfficiency = 0.5559978, minDamage = 151.6168, ammo = 0, ammo_type = 0, armorEfficiency = 0.5504938,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 4484.641, armor = 4433.517, rate = 0.7746316, drain = 0.9753991, maxDamage = 218.8319, shieldEfficiency = 0.5381947, minDamage = 154.7636, ammo = 0, ammo_type = 0, armorEfficiency = 0.5414202,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 4386.927, armor = 4424.979, rate = 2.867724, drain = 0.9953413, maxDamage = 656.3177, shieldEfficiency = 0.7344073, minDamage = 299.681, ammo = 5, ammo_type = 17, armorEfficiency = 0.7342361,},
}

ObjectTemplates:addTemplate(object_ship_smuggler_warlord_ship_tier2, "object/ship/smuggler_warlord_ship_tier2.iff")
