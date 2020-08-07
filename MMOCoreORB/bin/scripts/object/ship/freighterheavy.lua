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


object_ship_freighterheavy = object_ship_shared_freighterheavy:new {

	name = "freighterheavy",
	slideFactor = 2,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 99.39962, armor = 99.37106,},
	engine = { name = "eng_generic", hitpoints = 99.30485, armor = 96.62602, speed = 11.82202, pitch = 11.44094, roll = 11.93348, yaw = 11.87407, acceleration = 16.88803, rollRate = 19.61666, pitchRate = 19.82233, deceleration = 14.73611, yawRate = 19.39014,},
	shield_0 = { name = "shd_generic", hitpoints = 191.951, armor = 191.3009, regen = 4.764307, front = 581.4658, back = 781.3698,},
	armor_0 = { name = "arm_generic", hitpoints = 791.5966, armor = 763.525,},
	armor_1 = { name = "arm_generic", hitpoints = 763.6631, armor = 765.4579,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 68.18054, energy = 1683.681,},
	weapon_0 = { name = "wpn_generic", hitpoints = 192.4836, armor = 192.6696, rate = 0.669229, drain = 32.45982, maxDamage = 580.0009, shieldEfficiency = 0, minDamage = 314.336, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_freighterheavy, "object/ship/freighterheavy.iff")
