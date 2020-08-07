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


object_ship_lambdashuttle_tier4 = object_ship_shared_lambdashuttle_tier4:new {

	name = "lambdashuttle_tier4",
	slideFactor = 1.74,
	chassisHitpoints = 5760,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4082.507, armor = 4042.401,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4100.812, armor = 3972.913, speed = 45.13057, pitch = 24.64064, roll = 30.58562, yaw = 19.95985, acceleration = 10.71273, rollRate = 55.88639, pitchRate = 50.13318, deceleration = 9.327092, yawRate = 40.27712,},
	shield_0 = { name = "shd_generic", hitpoints = 3957.959, armor = 4062.035, regen = 29.19075, front = 31810.71, back = 31949.11,},
	armor_0 = { name = "arm_generic", hitpoints = 12999.64, armor = 13070.77,},
	armor_1 = { name = "arm_generic", hitpoints = 12937.19, armor = 12655.89,},
	capacitor = { name = "cap_generic", hitpoints = 4129.287, armor = 3961.08, rechargeRate = 95.06945, energy = 4891.95,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 4031.693, armor = 4119.346, rate = 0.7559092, drain = 0.9548265, maxDamage = 424.3986, shieldEfficiency = 0.5574844, minDamage = 279.0555, ammo = 0, ammo_type = 0, armorEfficiency = 0.5326153,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 4008.539, armor = 3986.044, rate = 0.7777123, drain = 0.956685, maxDamage = 423.3593, shieldEfficiency = 0.5354808, minDamage = 275.3408, ammo = 0, ammo_type = 0, armorEfficiency = 0.5418743,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier4, "object/ship/lambdashuttle_tier4.iff")
