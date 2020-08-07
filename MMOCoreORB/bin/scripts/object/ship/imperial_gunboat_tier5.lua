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


object_ship_imperial_gunboat_tier5 = object_ship_shared_imperial_gunboat_tier5:new {

	name = "imperial_gunboat_tier5",
	slideFactor = 1.81,
	chassisHitpoints = 24576,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 30763.42, armor = 30757.29,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 31308.46, armor = 31085.29, speed = 45.52637, pitch = 25.6121, roll = 30.90882, yaw = 19.96462, acceleration = 11.43887, rollRate = 57.18214, pitchRate = 51.99199, deceleration = 9.626505, yawRate = 41.51078,},
	shield_0 = { name = "shd_generic", hitpoints = 30565.28, armor = 30601.82, regen = 33.24294, front = 126353.4, back = 123902.2,},
	armor_0 = { name = "arm_generic", hitpoints = 65442.84, armor = 65517.49,},
	armor_1 = { name = "arm_generic", hitpoints = 66444.91, armor = 66455.86,},
	capacitor = { name = "cap_generic", hitpoints = 31422.69, armor = 30264.79, rechargeRate = 97.07323, energy = 4983.108,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 31790.75, armor = 30919.29, rate = 0.7537104, drain = 0.9772556, maxDamage = 797.1409, shieldEfficiency = 0.5331597, minDamage = 505.0874, ammo = 0, ammo_type = 0, armorEfficiency = 0.5353836,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 30284.7, armor = 30345.96, rate = 0.7636163, drain = 0.9738941, maxDamage = 782.4699, shieldEfficiency = 0.5454199, minDamage = 506.2316, ammo = 0, ammo_type = 0, armorEfficiency = 0.5403693,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 31318.02, armor = 30806.62, rate = 0.7489268, drain = 0.9518175, maxDamage = 797.7712, shieldEfficiency = 0.5461822, minDamage = 510.8389, ammo = 0, ammo_type = 0, armorEfficiency = 0.5554445,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 31101.57, armor = 30368.9, rate = 0.766303, drain = 0.9647605, maxDamage = 817.1663, shieldEfficiency = 0.5502174, minDamage = 502.5271, ammo = 0, ammo_type = 0, armorEfficiency = 0.5321889,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 30837.8, armor = 30672.92, rate = 0.7495723, drain = 0.9625373, maxDamage = 802.7571, shieldEfficiency = 0.5332296, minDamage = 494.3924, ammo = 0, ammo_type = 0, armorEfficiency = 0.5339559,},
	weapon_5 = { name = "wpn_tieadvanced_blaster", hitpoints = 30316.33, armor = 31606.51, rate = 0.7419247, drain = 0.9747093, maxDamage = 789.343, shieldEfficiency = 0.5557826, minDamage = 507.3188, ammo = 0, ammo_type = 0, armorEfficiency = 0.5461047,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat_tier5, "object/ship/imperial_gunboat_tier5.iff")
