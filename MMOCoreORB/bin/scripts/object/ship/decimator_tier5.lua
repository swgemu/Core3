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


object_ship_decimator_tier5 = object_ship_shared_decimator_tier5:new {

	name = "decimator_tier5",
	slideFactor = 1.69,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6213.783, armor = 6169.562,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6333.488, armor = 6068.055, speed = 46.19358, pitch = 25.95157, roll = 32.0527, yaw = 20.5666, acceleration = 11.17554, rollRate = 56.66952, pitchRate = 51.57581, deceleration = 9.476325, yawRate = 41.2345,},
	shield_0 = { name = "shd_generic", hitpoints = 6272.23, armor = 6227.235, regen = 44.97403, front = 24490.9, back = 24776.15,},
	armor_0 = { name = "arm_generic", hitpoints = 13149.71, armor = 13371.02,},
	armor_1 = { name = "arm_generic", hitpoints = 13461.51, armor = 13067.98,},
	capacitor = { name = "cap_generic", hitpoints = 6114.783, armor = 6159.52, rechargeRate = 95.43431, energy = 4996.06,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 6338.421, armor = 6169.612, rate = 0.7621536, drain = 0.9564594, maxDamage = 645.7781, shieldEfficiency = 0.5342806, minDamage = 394.8442, ammo = 0, ammo_type = 0, armorEfficiency = 0.55809,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 6215.98, armor = 6157.014, rate = 0.7714158, drain = 0.98356, maxDamage = 634.941, shieldEfficiency = 0.5561679, minDamage = 406.9753, ammo = 0, ammo_type = 0, armorEfficiency = 0.5535206,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 6275.778, armor = 6297.312, rate = 2.860839, drain = 0.9752573, maxDamage = 1946.615, shieldEfficiency = 0.7331694, minDamage = 819.6271, ammo = 4, ammo_type = 20, armorEfficiency = 0.741452,},
}

ObjectTemplates:addTemplate(object_ship_decimator_tier5, "object/ship/decimator_tier5.iff")
