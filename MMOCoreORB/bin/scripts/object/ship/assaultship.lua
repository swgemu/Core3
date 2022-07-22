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


object_ship_assaultship = object_ship_shared_assaultship:new {

	name = "assaultship",
	slideFactor = 1,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.05299, armor = 97.72736,},
	engine = { name = "eng_generic", hitpoints = 98.83556, armor = 99.14944, speed = 49.88302, pitch = 23.05017, roll = 23.42142, yaw = 23.26724, acceleration = 42.61156, rollRate = 39.9012, pitchRate = 39.71355, deceleration = 36.90677, yawRate = 41.06225,},
	shield_0 = { name = "shd_generic", hitpoints = 194.4048, armor = 190.9529, regen = 4.923894, front = 194.4937, back = 194.8526,},
	armor_0 = { name = "arm_generic", hitpoints = 781.739, armor = 766.9294,},
	armor_1 = { name = "arm_generic", hitpoints = 782.1686, armor = 787.6256,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 137.9457, energy = 3442.146,},
	weapon_0 = { name = "wpn_generic", hitpoints = 199.3354, armor = 191.032, rate = 1.31652, drain = 64.17976, maxDamage = 247.0937, shieldEfficiency = 0, minDamage = 118.0961, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_assaultship, "object/ship/assaultship.iff")
