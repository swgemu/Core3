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


object_ship_ykl37r_tier5 = object_ship_shared_ykl37r_tier5:new {

	name = "ykl37r_tier5",
	slideFactor = 1.79,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6345.765, armor = 6319.584,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6160.572, armor = 6226.914, speed = 45.57482, pitch = 25.90091, roll = 30.98989, yaw = 20.25834, acceleration = 11.16971, rollRate = 58.58983, pitchRate = 51.62413, deceleration = 9.634668, yawRate = 42.97672,},
	shield_0 = { name = "shd_generic", hitpoints = 6182.508, armor = 6067.054, regen = 45.17753, front = 25113.22, back = 24412.22,},
	armor_0 = { name = "arm_generic", hitpoints = 13453.99, armor = 13073.59,},
	armor_1 = { name = "arm_generic", hitpoints = 13514.75, armor = 13576.08,},
	capacitor = { name = "cap_generic", hitpoints = 6360.022, armor = 6120.945, rechargeRate = 97.96063, energy = 4870.613,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 6328.02, armor = 6201.961, rate = 0.7640949, drain = 0.9852272, maxDamage = 627.6688, shieldEfficiency = 0.5538287, minDamage = 394.6765, ammo = 0, ammo_type = 0, armorEfficiency = 0.5508229,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 6198.69, armor = 6366.98, rate = 0.7545359, drain = 0.9642752, maxDamage = 654.0597, shieldEfficiency = 0.54471, minDamage = 398.9518, ammo = 0, ammo_type = 0, armorEfficiency = 0.5362911,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 6284.74, armor = 6262.795, rate = 2.953953, drain = 0.9807301, maxDamage = 1972.713, shieldEfficiency = 0.721887, minDamage = 804.3573, ammo = 4, ammo_type = 20, armorEfficiency = 0.7172034,},
}

ObjectTemplates:addTemplate(object_ship_ykl37r_tier5, "object/ship/ykl37r_tier5.iff")
