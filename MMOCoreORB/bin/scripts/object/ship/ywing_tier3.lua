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


object_ship_ywing_tier3 = object_ship_shared_ywing_tier3:new {

	name = "ywing_tier3",
	slideFactor = 1.77,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1031.282, armor = 1032.317,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1035.357, armor = 1048.259, speed = 44.07818, pitch = 23.64441, roll = 29.75775, yaw = 18.8736, acceleration = 10.46538, rollRate = 52.96029, pitchRate = 46.573, deceleration = 8.865496, yawRate = 40.02581,},
	shield_0 = { name = "shd_generic", hitpoints = 1072.706, armor = 1070.61, regen = 9.019173, front = 4211.66, back = 4106.937,},
	armor_0 = { name = "arm_generic", hitpoints = 2414.644, armor = 2484.1,},
	armor_1 = { name = "arm_generic", hitpoints = 2493.55, armor = 2413.412,},
	capacitor = { name = "cap_generic", hitpoints = 1036.099, armor = 1029.437, rechargeRate = 98.32436, energy = 4904.901,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 1054.026, armor = 1072.64, rate = 0.7519579, drain = 0.9641545, maxDamage = 161.2065, shieldEfficiency = 0.537326, minDamage = 110.471, ammo = 0, ammo_type = 0, armorEfficiency = 0.5572495,},
	weapon_1 = { name = "wpn_slayn_ioncannon", hitpoints = 1026.476, armor = 1029.1, rate = 0.7786238, drain = 0.9959017, maxDamage = 157.7175, shieldEfficiency = 0.5440833, minDamage = 107.868, ammo = 0, ammo_type = 0, armorEfficiency = 0.5598337,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1035.747, armor = 1067.632, rate = 2.932887, drain = 0.9589483, maxDamage = 466.9039, shieldEfficiency = 0.7148442, minDamage = 220.7479, ammo = 4, ammo_type = 18, armorEfficiency = 0.7368108,},
}

ObjectTemplates:addTemplate(object_ship_ywing_tier3, "object/ship/ywing_tier3.iff")
