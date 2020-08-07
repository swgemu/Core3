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


object_ship_tieadvanced_tier2 = object_ship_shared_tieadvanced_tier2:new {

	name = "tieadvanced_tier2",
	slideFactor = 1.76,
	chassisHitpoints = 720,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 531.5491, armor = 526.5476,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 516.1342, armor = 539.2276, speed = 41.53335, pitch = 23.15852, roll = 29.08084, yaw = 18.21366, acceleration = 10.26803, rollRate = 52.97118, pitchRate = 46.49741, deceleration = 8.547914, yawRate = 38.4377,},
	shield_0 = { name = "shd_generic", hitpoints = 513.8074, armor = 529.7487, regen = 6.303245, front = 2130.151, back = 2142.544,},
	armor_0 = { name = "arm_generic", hitpoints = 1098.192, armor = 1124.249,},
	armor_1 = { name = "arm_generic", hitpoints = 1134.28, armor = 1118.483,},
	capacitor = { name = "cap_generic", hitpoints = 515.2714, armor = 538.2487, rechargeRate = 99.61189, energy = 4966.947,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 523.8036, armor = 513.7527, rate = 0.7631401, drain = 0.9614477, maxDamage = 101.5167, shieldEfficiency = 0.5438342, minDamage = 71.8738, ammo = 0, ammo_type = 0, armorEfficiency = 0.5451878,},
}

ObjectTemplates:addTemplate(object_ship_tieadvanced_tier2, "object/ship/tieadvanced_tier2.iff")
