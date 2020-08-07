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


object_ship_smuggler_warlord_ship_tier1 = object_ship_shared_smuggler_warlord_ship_tier1:new {

	name = "smuggler_warlord_ship_tier1",
	slideFactor = 1.76,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1489.651, armor = 1480.835,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1449.862, armor = 1463.342, speed = 40.26495, pitch = 22.04785, roll = 27.91575, yaw = 18.27823, acceleration = 10.10918, rollRate = 51.94538, pitchRate = 45.31192, deceleration = 8.323958, yawRate = 36.87482,},
	shield_0 = { name = "shd_generic", hitpoints = 1456.314, armor = 1439.942, regen = 4.351389, front = 5826.081, back = 5836.717,},
	armor_0 = { name = "arm_generic", hitpoints = 3049.616, armor = 3056.251,},
	armor_1 = { name = "arm_generic", hitpoints = 3046.608, armor = 3059.189,},
	capacitor = { name = "cap_generic", hitpoints = 1475.344, armor = 1479.882, rechargeRate = 98.03831, energy = 4927.807,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 1499.73, armor = 1458.655, rate = 0.7756778, drain = 0.9670949, maxDamage = 95.26437, shieldEfficiency = 0.5503489, minDamage = 72.28418, ammo = 0, ammo_type = 0, armorEfficiency = 0.5584059,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 1434.689, armor = 1441.974, rate = 0.7708731, drain = 0.988616, maxDamage = 99.37067, shieldEfficiency = 0.5477311, minDamage = 72.70628, ammo = 0, ammo_type = 0, armorEfficiency = 0.5481986,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 1443.172, armor = 1449.318, rate = 0.7591377, drain = 0.9720508, maxDamage = 96.20347, shieldEfficiency = 0.5414121, minDamage = 71.8951, ammo = 0, ammo_type = 0, armorEfficiency = 0.5490009,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 1485.435, armor = 1436.625, rate = 0.7490533, drain = 0.9775068, maxDamage = 99.71967, shieldEfficiency = 0.5509492, minDamage = 71.68753, ammo = 0, ammo_type = 0, armorEfficiency = 0.5381601,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1472.041, armor = 1469.429, rate = 2.890321, drain = 0.9900565, maxDamage = 297.7009, shieldEfficiency = 0.7473453, minDamage = 146.8271, ammo = 5, ammo_type = 16, armorEfficiency = 0.7199096,},
}

ObjectTemplates:addTemplate(object_ship_smuggler_warlord_ship_tier1, "object/ship/smuggler_warlord_ship_tier1.iff")
