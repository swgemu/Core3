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


object_ship_tiefighter = object_ship_shared_tiefighter:new {

	name = "tiefighter",
	slideFactor = 1.75,
	chassisHitpoints = 412,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.66823, armor = 97.91923,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 98.51554, armor = 95.67663, speed = 46.61049, pitch = 25.72686, roll = 26.27263, yaw = 25.22962, acceleration = 13.75706, rollRate = 51.67604, pitchRate = 49.51648, deceleration = 6.24891, yawRate = 51.30093,},
	shield_0 = { name = "shd_generic", hitpoints = 195.9958, armor = 192.1979, regen = 4.863165, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 496.286, armor = 479.5057,},
	armor_1 = { name = "arm_generic", hitpoints = 477.4287, armor = 494.0988,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 50.30202, energy = 1301.678,},
	weapon_0 = { name = "wpn_generic", hitpoints = 191.6802, armor = 199.1543, rate = 0.5004961, drain = 23.46581, maxDamage = 214.6875, shieldEfficiency = 0, minDamage = 174.0569, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 190.7315, armor = 193.5563, rate = 2.854056, drain = 23.98825, maxDamage = 24.42323, shieldEfficiency = 0, minDamage = 24.53417, ammo = 50, ammo_type = 2, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 19.76241, armor = 19.88882, rate = 0.9672338, drain = 24.54323, maxDamage = 23.83581, shieldEfficiency = 0, minDamage = 24.31078, ammo = 50, ammo_type = 7, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter, "object/ship/tiefighter.iff")
