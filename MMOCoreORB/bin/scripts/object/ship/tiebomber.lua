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


object_ship_tiebomber = object_ship_shared_tiebomber:new {

	name = "tiebomber",
	slideFactor = 1.75,
	chassisHitpoints = 544,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.44814, armor = 97.97638,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 99.02635, armor = 95.88634, speed = 48.42047, pitch = 12.20292, roll = 11.88856, yaw = 11.89604, acceleration = 19.29764, rollRate = 24.35385, pitchRate = 23.67579, deceleration = 15.41817, yawRate = 23.825,},
	shield_0 = { name = "shd_generic", hitpoints = 191.9901, armor = 197.8472, regen = 4.901892, front = 695.264, back = 889.9745,},
	armor_0 = { name = "arm_generic", hitpoints = 776.0244, armor = 761.0108,},
	armor_1 = { name = "arm_generic", hitpoints = 788.7833, armor = 761.546,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 66.52002, energy = 1680.317,},
	weapon_0 = { name = "wpn_generic", hitpoints = 192.7133, armor = 192.7953, rate = 0.6476261, drain = 31.61043, maxDamage = 412.7628, shieldEfficiency = 0, minDamage = 300.4712, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 195.5404, armor = 196.7177, rate = 1.93973, drain = 31.74503, maxDamage = 32.72117, shieldEfficiency = 0, minDamage = 31.45617, ammo = 50, ammo_type = 3, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 19.223, armor = 19.90419, rate = 1.965723, drain = 31.33873, maxDamage = 32.57617, shieldEfficiency = 0, minDamage = 31.56183, ammo = 50, ammo_type = 3, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber, "object/ship/tiebomber.iff")
