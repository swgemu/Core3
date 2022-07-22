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


object_ship_imperial_gunboat_tier4 = object_ship_shared_imperial_gunboat_tier4:new {

	name = "imperial_gunboat_tier4",
	slideFactor = 1.81,
	chassisHitpoints = 19200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 20042.15, armor = 20085.69,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 19846.47, armor = 20104.55, speed = 45.88789, pitch = 25.05605, roll = 30.59983, yaw = 19.34768, acceleration = 10.87502, rollRate = 55.52969, pitchRate = 48.54793, deceleration = 9.174951, yawRate = 40.87846,},
	shield_0 = { name = "shd_generic", hitpoints = 20661.74, armor = 19890, regen = 21.61406, front = 78800.37, back = 80791.37,},
	armor_0 = { name = "arm_generic", hitpoints = 42894.5, armor = 42758.18,},
	armor_1 = { name = "arm_generic", hitpoints = 42982.62, armor = 44076.32,},
	capacitor = { name = "cap_generic", hitpoints = 20242.8, armor = 19795.48, rechargeRate = 99.16365, energy = 4959.151,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 20414.52, armor = 20370.26, rate = 0.750233, drain = 0.9973189, maxDamage = 617.0654, shieldEfficiency = 0.5487376, minDamage = 407.1566, ammo = 0, ammo_type = 0, armorEfficiency = 0.5535373,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 20504.39, armor = 20308.7, rate = 0.7518762, drain = 0.9533567, maxDamage = 609.5172, shieldEfficiency = 0.5401061, minDamage = 398.2353, ammo = 0, ammo_type = 0, armorEfficiency = 0.5507846,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 20145.24, armor = 20281.76, rate = 0.7654139, drain = 0.9564163, maxDamage = 622.908, shieldEfficiency = 0.5453085, minDamage = 407.2535, ammo = 0, ammo_type = 0, armorEfficiency = 0.5446158,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 20368.02, armor = 20643.71, rate = 0.7783946, drain = 0.9584152, maxDamage = 611.3662, shieldEfficiency = 0.5353906, minDamage = 405.2898, ammo = 0, ammo_type = 0, armorEfficiency = 0.5379745,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 19902.11, armor = 19928.26, rate = 0.7481144, drain = 0.9972379, maxDamage = 611.1364, shieldEfficiency = 0.551781, minDamage = 402.6162, ammo = 0, ammo_type = 0, armorEfficiency = 0.5474001,},
	weapon_5 = { name = "wpn_tieadvanced_blaster", hitpoints = 20623.64, armor = 20341.21, rate = 0.753794, drain = 0.9764425, maxDamage = 608.2877, shieldEfficiency = 0.5442464, minDamage = 398.6884, ammo = 0, ammo_type = 0, armorEfficiency = 0.5567312,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat_tier4, "object/ship/imperial_gunboat_tier4.iff")
