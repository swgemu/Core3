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


object_ship_ykl37r_tier4 = object_ship_shared_ykl37r_tier4:new {

	name = "ykl37r_tier4",
	slideFactor = 1.79,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3948.052, armor = 4068.48,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4059.699, armor = 4109.605, speed = 45.63183, pitch = 24.91853, roll = 30.14256, yaw = 19.46673, acceleration = 11.09466, rollRate = 56.48645, pitchRate = 49.78278, deceleration = 9.375684, yawRate = 40.44704,},
	shield_0 = { name = "shd_generic", hitpoints = 3957.563, armor = 4046.571, regen = 29.07651, front = 16427.06, back = 16286.59,},
	armor_0 = { name = "arm_generic", hitpoints = 8672.588, armor = 8773.767,},
	armor_1 = { name = "arm_generic", hitpoints = 8828.599, armor = 8480.08,},
	capacitor = { name = "cap_generic", hitpoints = 4112.46, armor = 3991.221, rechargeRate = 97.39368, energy = 4877.171,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 3959.322, armor = 3944.457, rate = 0.7475221, drain = 0.9842595, maxDamage = 504.07, shieldEfficiency = 0.5334319, minDamage = 329.0294, ammo = 0, ammo_type = 0, armorEfficiency = 0.5455862,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 3957.831, armor = 3985.238, rate = 0.7657736, drain = 0.9580226, maxDamage = 498.9513, shieldEfficiency = 0.5368012, minDamage = 324.8485, ammo = 0, ammo_type = 0, armorEfficiency = 0.5568369,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 4011.019, armor = 3975.749, rate = 2.921488, drain = 0.9994758, maxDamage = 1463.035, shieldEfficiency = 0.7495089, minDamage = 651.8242, ammo = 4, ammo_type = 19, armorEfficiency = 0.7455894,},
}

ObjectTemplates:addTemplate(object_ship_ykl37r_tier4, "object/ship/ykl37r_tier4.iff")
