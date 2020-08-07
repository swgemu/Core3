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


object_ship_droid_fighter = object_ship_shared_droid_fighter:new {

	name = "droid_fighter",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 296.3893, armor = 290.6176,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.5463, armor = 98.54914, speed = 42.95467, pitch = 30.48932, roll = 31.86797, yaw = 31.35491, acceleration = 10.12654, rollRate = 57.19476, pitchRate = 57.74682, deceleration = 4.344702, yawRate = 59.24586,},
	shield_0 = { name = "shd_generic", hitpoints = 382.2277, armor = 475.8343, regen = 4.751729, front = 298.3941, back = 392.1485,},
	armor_0 = { name = "arm_generic", hitpoints = 191.9277, armor = 198.3179,},
	armor_1 = { name = "arm_generic", hitpoints = 198.958, armor = 197.0928,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.41519, energy = 552.1365,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 194.5731, armor = 199.6548, rate = 0.3414823, drain = 23.16827, maxDamage = 244.3353, shieldEfficiency = 0, minDamage = 118.6522, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter, "object/ship/droid_fighter.iff")
