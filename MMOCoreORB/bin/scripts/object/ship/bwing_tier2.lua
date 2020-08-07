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


object_ship_bwing_tier2 = object_ship_shared_bwing_tier2:new {

	name = "bwing_tier2",
	slideFactor = 1.67,
	chassisHitpoints = 720,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 523.9122, armor = 530.3552,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 521.6395, armor = 538.2982, speed = 42.53133, pitch = 23.26379, roll = 28.95224, yaw = 18.25059, acceleration = 10.00936, rollRate = 52.23365, pitchRate = 47.51831, deceleration = 8.542104, yawRate = 37.87012,},
	shield_0 = { name = "shd_generic", hitpoints = 539.1285, armor = 526.4113, regen = 5.36134, front = 2080.029, back = 2142.835,},
	armor_0 = { name = "arm_generic", hitpoints = 1121.877, armor = 1116.297,},
	armor_1 = { name = "arm_generic", hitpoints = 1106.705, armor = 1112.491,},
	capacitor = { name = "cap_generic", hitpoints = 533.8638, armor = 521.2041, rechargeRate = 96.34903, energy = 4974.97,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 530.0679, armor = 524.6187, rate = 0.7559597, drain = 0.9943858, maxDamage = 92.07744, shieldEfficiency = 0.5536531, minDamage = 68.76481, ammo = 0, ammo_type = 0, armorEfficiency = 0.5401579,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 533.0776, armor = 537.6251, rate = 0.7667242, drain = 0.9908034, maxDamage = 92.55042, shieldEfficiency = 0.5373799, minDamage = 68.07294, ammo = 0, ammo_type = 0, armorEfficiency = 0.5393872,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 517.2496, armor = 521.9507, rate = 0.7658105, drain = 0.9521518, maxDamage = 92.08702, shieldEfficiency = 0.5340269, minDamage = 66.89284, ammo = 0, ammo_type = 0, armorEfficiency = 0.5507624,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 515.9511, armor = 513.321, rate = 0.7725638, drain = 0.9689018, maxDamage = 92.74501, shieldEfficiency = 0.5586295, minDamage = 68.06882, ammo = 0, ammo_type = 0, armorEfficiency = 0.5422171,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 534.6283, armor = 518.2376, rate = 2.89955, drain = 0.9967572, maxDamage = 286.6354, shieldEfficiency = 0.7304196, minDamage = 138.3739, ammo = 4, ammo_type = 17, armorEfficiency = 0.7256553,},
}

ObjectTemplates:addTemplate(object_ship_bwing_tier2, "object/ship/bwing_tier2.iff")
