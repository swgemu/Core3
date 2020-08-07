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


object_ship_droid_fighter_tier3 = object_ship_shared_droid_fighter_tier3:new {

	name = "droid_fighter_tier3",
	slideFactor = 1.92,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1033.787, armor = 1068.072,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1058.717, armor = 1069.434, speed = 43.48965, pitch = 24.50116, roll = 29.74688, yaw = 18.88317, acceleration = 10.70723, rollRate = 54.51667, pitchRate = 48.433, deceleration = 9.080114, yawRate = 39.79525,},
	shield_0 = { name = "shd_generic", hitpoints = 1046.47, armor = 1028.928, regen = 9.110542, front = 4166.393, back = 4283.999,},
	armor_0 = { name = "arm_generic", hitpoints = 2258.287, armor = 2277.863,},
	armor_1 = { name = "arm_generic", hitpoints = 2276.566, armor = 2245.203,},
	capacitor = { name = "cap_generic", hitpoints = 1069.301, armor = 1075.483, rechargeRate = 97.63407, energy = 4777.794,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 1035.514, armor = 1035.528, rate = 0.763121, drain = 0.9514323, maxDamage = 161.3009, shieldEfficiency = 0.54449, minDamage = 108.2523, ammo = 0, ammo_type = 0, armorEfficiency = 0.5361369,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier3, "object/ship/droid_fighter_tier3.iff")
