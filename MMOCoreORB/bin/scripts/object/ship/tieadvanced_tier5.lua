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


object_ship_tieadvanced_tier5 = object_ship_shared_tieadvanced_tier5:new {

	name = "tieadvanced_tier5",
	slideFactor = 1.76,
	chassisHitpoints = 2949.12,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3650.285, armor = 3791.114,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 3701.757, armor = 3754.182, speed = 45.67072, pitch = 24.78212, roll = 31.60044, yaw = 19.6447, acceleration = 11.13632, rollRate = 57.50341, pitchRate = 51.20527, deceleration = 9.766382, yawRate = 43.09169,},
	shield_0 = { name = "shd_generic", hitpoints = 3778.119, armor = 3719.625, regen = 26.80195, front = 14607.55, back = 15106.6,},
	armor_0 = { name = "arm_generic", hitpoints = 7956.286, armor = 7864.966,},
	armor_1 = { name = "arm_generic", hitpoints = 7997.001, armor = 8080.612,},
	capacitor = { name = "cap_generic", hitpoints = 3766.549, armor = 3806.723, rechargeRate = 96.91192, energy = 4795.805,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 3770.979, armor = 3731.452, rate = 0.7529407, drain = 0.9924043, maxDamage = 389.4767, shieldEfficiency = 0.5410508, minDamage = 243.5872, ammo = 0, ammo_type = 0, armorEfficiency = 0.5521652,},
}

ObjectTemplates:addTemplate(object_ship_tieadvanced_tier5, "object/ship/tieadvanced_tier5.iff")
