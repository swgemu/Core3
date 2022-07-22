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


object_ship_civshuttle = object_ship_shared_civshuttle:new {

	name = "civshuttle",
	slideFactor = 1,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.79517, armor = 95.32833,},
	engine = { name = "eng_generic", hitpoints = 98.26923, armor = 95.88637, speed = 29.13935, pitch = 15.95895, roll = 15.64491, yaw = 16.1961, acceleration = 25.73766, rollRate = 19.88272, pitchRate = 19.9164, deceleration = 21.83313, yawRate = 19.63519,},
	shield_0 = { name = "shd_generic", hitpoints = 198.1622, armor = 192.1963, regen = 4.757228, front = 193.7592, back = 190.4718,},
	armor_0 = { name = "arm_generic", hitpoints = 199.2556, armor = 198.116,},
	armor_1 = { name = "arm_generic", hitpoints = 196.3457, armor = 191.361,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 17.32041, energy = 430.8173,},
	weapon_0 = { name = "wpn_generic", hitpoints = 197.1109, armor = 193.2701, rate = 0.1623135, drain = 7.997119, maxDamage = 247.1539, shieldEfficiency = 0, minDamage = 116.933, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_civshuttle, "object/ship/civshuttle.iff")
