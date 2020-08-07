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


object_ship_tieaggressor_tier5 = object_ship_shared_tieaggressor_tier5:new {

	name = "tieaggressor_tier5",
	slideFactor = 1.68,
	chassisHitpoints = 2457.6,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3172.304, armor = 3163.251,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 3089.191, armor = 3075.223, speed = 45.25795, pitch = 24.77656, roll = 31.81954, yaw = 20.40435, acceleration = 11.02026, rollRate = 57.15804, pitchRate = 51.59002, deceleration = 9.646002, yawRate = 42.09367,},
	shield_0 = { name = "shd_generic", hitpoints = 3182.646, armor = 3076.987, regen = 22.29093, front = 12338.92, back = 12378.14,},
	armor_0 = { name = "arm_generic", hitpoints = 6538.216, armor = 6502.718,},
	armor_1 = { name = "arm_generic", hitpoints = 6483.104, armor = 6716.164,},
	capacitor = { name = "cap_generic", hitpoints = 3073.342, armor = 3132.545, rechargeRate = 95.1771, energy = 4935.667,},
	weapon_0 = { name = "wpn_generic", hitpoints = 3075.698, armor = 3077.687, rate = 0.7502176, drain = 0.9653783, maxDamage = 348.93, shieldEfficiency = 0.5353479, minDamage = 217.2645, ammo = 0, ammo_type = 0, armorEfficiency = 0.5478718,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 3028.872, armor = 3093.898, rate = 0.7463202, drain = 0.9869664, maxDamage = 345.3698, shieldEfficiency = 0.5353292, minDamage = 224.1246, ammo = 0, ammo_type = 0, armorEfficiency = 0.5416447,},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor_tier5, "object/ship/tieaggressor_tier5.iff")
