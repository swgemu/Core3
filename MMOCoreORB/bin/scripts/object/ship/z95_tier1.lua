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


object_ship_z95_tier1 = object_ship_shared_z95_tier1:new {

	name = "z95_tier1",
	slideFactor = 1.84,
	chassisHitpoints = 240,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 149.4781, armor = 145.8624,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 149.5125, armor = 147.3826, speed = 45.35249, pitch = 22.99485, roll = 28.30181, yaw = 17.79153, acceleration = 11.06643, rollRate = 50.31916, pitchRate = 45.89691, deceleration = 8.321511, yawRate = 37.15811,},
	shield_0 = { name = "shd_generic", hitpoints = 145.0518, armor = 144.8831, regen = 2.855887, front = 637.6353, back = 646.3284,},
	armor_0 = { name = "arm_generic", hitpoints = 251.5578, armor = 245.3948,},
	armor_1 = { name = "arm_generic", hitpoints = 254.6567, armor = 245.3695,},
	capacitor = { name = "cap_generic", hitpoints = 147.5147, armor = 146.9473, rechargeRate = 96.12499, energy = 4768.983,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 146.542, armor = 148.6743, rate = 0.7472869, drain = 0.9663234, maxDamage = 36.30932, shieldEfficiency = 0.548558, minDamage = 28.43193, ammo = 0, ammo_type = 0, armorEfficiency = 0.558629,},
}

ObjectTemplates:addTemplate(object_ship_z95_tier1, "object/ship/z95_tier1.iff")
