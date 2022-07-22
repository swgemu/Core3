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


object_ship_awing_tier2 = object_ship_shared_awing_tier2:new {

	name = "awing_tier2",
	slideFactor = 1.62,
	chassisHitpoints = 540,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 386.0601, armor = 391.8838,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 402.0693, armor = 396.6858, speed = 46.27, pitch = 23.18811, roll = 28.0745, yaw = 18.60315, acceleration = 11.27654, rollRate = 52.09315, pitchRate = 46.66763, deceleration = 8.721692, yawRate = 37.62374,},
	shield_0 = { name = "shd_generic", hitpoints = 401.7253, armor = 385.9196, regen = 5.273414, front = 1595.751, back = 1574.382,},
	armor_0 = { name = "arm_generic", hitpoints = 831.3472, armor = 838.4591,},
	armor_1 = { name = "arm_generic", hitpoints = 834.0142, armor = 863.635,},
	capacitor = { name = "cap_generic", hitpoints = 384.8815, armor = 388.2174, rechargeRate = 95.01259, energy = 4965.907,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 391.277, armor = 389.6266, rate = 0.7569824, drain = 0.9798223, maxDamage = 84.37731, shieldEfficiency = 0.5361491, minDamage = 61.3644, ammo = 0, ammo_type = 0, armorEfficiency = 0.5470703,},
}

ObjectTemplates:addTemplate(object_ship_awing_tier2, "object/ship/awing_tier2.iff")
