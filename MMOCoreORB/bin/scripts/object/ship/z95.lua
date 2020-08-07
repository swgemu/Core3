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


object_ship_z95 = object_ship_shared_z95:new {

	name = "z95",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 294.977, armor = 297.7502,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.82836, armor = 97.21703, speed = 43.4332, pitch = 21.19557, roll = 20.36089, yaw = 20.40409, acceleration = 9.865755, rollRate = 45.95029, pitchRate = 47.79227, deceleration = 4.498515, yawRate = 47.44696,},
	shield_0 = { name = "shd_generic", hitpoints = 396.6587, armor = 478.8398, regen = 4.881178, front = 291.0807, back = 479.8737,},
	armor_0 = { name = "arm_generic", hitpoints = 396.9427, armor = 395.786,},
	armor_1 = { name = "arm_generic", hitpoints = 396.0852, armor = 383.4976,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.53789, energy = 545.7473,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 198.6331, armor = 196.5267, rate = 0.3351864, drain = 22.8655, maxDamage = 214.437, shieldEfficiency = 0, minDamage = 115.8905, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_seismic_missile_s01", hitpoints = 196.3027, armor = 199.3198, rate = 2.961795, drain = 22.67604, maxDamage = 22.52807, shieldEfficiency = 0, minDamage = 23.36712, ammo = 50, ammo_type = 5, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_z95, "object/ship/z95.iff")
