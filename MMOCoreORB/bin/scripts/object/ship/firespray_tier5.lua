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


object_ship_firespray_tier5 = object_ship_shared_firespray_tier5:new {

	name = "firespray_tier5",
	slideFactor = 1.81,
	chassisHitpoints = 3194.88,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4015.877, armor = 4133.67,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4078.136, armor = 3992.828, speed = 46.74838, pitch = 25.3824, roll = 30.77517, yaw = 19.8431, acceleration = 11.32218, rollRate = 58.19091, pitchRate = 50.49698, deceleration = 9.329021, yawRate = 41.80019,},
	shield_0 = { name = "shd_generic", hitpoints = 4071.783, armor = 4042.843, regen = 29.29023, front = 15814.37, back = 15945.1,},
	armor_0 = { name = "arm_generic", hitpoints = 8819.48, armor = 8795.444,},
	armor_1 = { name = "arm_generic", hitpoints = 8490.255, armor = 8620.789,},
	capacitor = { name = "cap_generic", hitpoints = 4115.206, armor = 4075.563, rechargeRate = 97.09749, energy = 4849.132,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 4035.822, armor = 3967.321, rate = 0.7433927, drain = 0.9572116, maxDamage = 408.2977, shieldEfficiency = 0.5537603, minDamage = 254.644, ammo = 0, ammo_type = 0, armorEfficiency = 0.549074,},
}

ObjectTemplates:addTemplate(object_ship_firespray_tier5, "object/ship/firespray_tier5.iff")
