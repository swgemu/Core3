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


object_ship_player_player_awing = object_ship_player_shared_player_awing:new {

	name = "player_awing",
	slideFactor = 1.68,
	chassisHitpoints = 1125,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.4938, armor = 293.254,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.62638, armor = 99.53873, speed = 58.49604, pitch = 54.38784, roll = 51.79129, yaw = 51.6744, acceleration = 15.62266, rollRate = 71.09726, pitchRate = 66.57938, deceleration = 10.89445, yawRate = 65.4823,},
	shield_0 = { name = "shd_generic", hitpoints = 389.9558, armor = 483.2215, regen = 3.978801, front = 583.4476, back = 588.3502,},
	armor_0 = { name = "arm_generic", hitpoints = 368.3198, armor = 374.6463,},
	armor_1 = { name = "arm_generic", hitpoints = 372.1447, armor = 363.5598,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 37.40336, energy = 590.8511,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 192.7826, armor = 196.4264, rate = 0.3420266, drain = 24.23798, maxDamage = 488.6028, shieldEfficiency = 0, minDamage = 343.2561, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_slayn_imagerec_missile_s01", hitpoints = 195.1021, armor = 190.1535, rate = 9.298404, drain = 22.53142, maxDamage = 721.2959, shieldEfficiency = 0.7642616, minDamage = 319.8891, ammo = 16, ammo_type = 5, armorEfficiency = 0.3130159,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 245.7827, armor = 245.6506, rate = 0.09964385, drain = 23.41895, maxDamage = 95.01245, shieldEfficiency = 0, minDamage = 23.99893, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_awing, "object/ship/player/player_awing.iff")
