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


object_ship_tie_light_duty = object_ship_shared_tie_light_duty:new {

	name = "tie_light_duty",
	slideFactor = 1.75,
	chassisHitpoints = 412,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 95.23991, armor = 97.1245,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 96.58778, armor = 95.75064, speed = 46.11737, pitch = 25.48482, roll = 26.3555, yaw = 25.28878, acceleration = 13.56986, rollRate = 49.44342, pitchRate = 51.63694, deceleration = 6.116066, yawRate = 49.81473,},
	shield_0 = { name = "shd_generic", hitpoints = 196.9696, armor = 197.7267, regen = 4.867599, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 499.7167, armor = 488.1603,},
	armor_1 = { name = "arm_generic", hitpoints = 484.8329, armor = 486.3284,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 51.43729, energy = 1281.657,},
	weapon_0 = { name = "wpn_generic", hitpoints = 193.3558, armor = 191.4244, rate = 0.4842786, drain = 23.55643, maxDamage = 212.8721, shieldEfficiency = 0, minDamage = 177.4314, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 190.9892, armor = 195.8387, rate = 2.858269, drain = 24.05192, maxDamage = 23.34772, shieldEfficiency = 0, minDamage = 24.32142, ammo = 50, ammo_type = 2, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 19.8271, armor = 19.0726, rate = 0.9595686, drain = 23.81435, maxDamage = 23.87384, shieldEfficiency = 0, minDamage = 23.95187, ammo = 50, ammo_type = 7, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tie_light_duty, "object/ship/tie_light_duty.iff")
