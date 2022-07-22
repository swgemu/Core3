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


object_ship_firespray_tier1 = object_ship_shared_firespray_tier1:new {

	name = "firespray_tier1",
	slideFactor = 1.81,
	chassisHitpoints = 312,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 194.5643, armor = 194.6988,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 192.8934, armor = 190.9095, speed = 41.74037, pitch = 22.01379, roll = 27.44349, yaw = 17.84049, acceleration = 9.725011, rollRate = 50.61102, pitchRate = 43.89222, deceleration = 8.613929, yawRate = 37.67494,},
	shield_0 = { name = "shd_generic", hitpoints = 188.5201, armor = 185.8557, regen = 3.759284, front = 745.793, back = 761.1376,},
	armor_0 = { name = "arm_generic", hitpoints = 410.9492, armor = 412.6464,},
	armor_1 = { name = "arm_generic", hitpoints = 398.1259, armor = 398.6513,},
	capacitor = { name = "cap_generic", hitpoints = 192.5222, armor = 192.6187, rechargeRate = 99.29137, energy = 4764.709,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 194.9763, armor = 187.346, rate = 0.7436996, drain = 0.9682803, maxDamage = 50.242, shieldEfficiency = 0.5566823, minDamage = 38.52365, ammo = 0, ammo_type = 0, armorEfficiency = 0.5485356,},
}

ObjectTemplates:addTemplate(object_ship_firespray_tier1, "object/ship/firespray_tier1.iff")
