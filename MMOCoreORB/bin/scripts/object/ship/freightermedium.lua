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


object_ship_freightermedium = object_ship_shared_freightermedium:new {

	name = "freightermedium",
	slideFactor = 2,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.48953, armor = 99.59495,},
	engine = { name = "eng_generic", hitpoints = 97.34251, armor = 95.45883, speed = 15.46101, pitch = 15.28065, roll = 15.71315, yaw = 15.80318, acceleration = 25.47562, rollRate = 21.65451, pitchRate = 21.32055, deceleration = 22.05575, yawRate = 21.03679,},
	shield_0 = { name = "shd_generic", hitpoints = 192.3368, armor = 194.2559, regen = 4.926056, front = 398.8176, back = 677.7628,},
	armor_0 = { name = "arm_generic", hitpoints = 596.9176, armor = 574.3787,},
	armor_1 = { name = "arm_generic", hitpoints = 573.0746, armor = 584.9464,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.49744, energy = 831.6958,},
	weapon_0 = { name = "wpn_generic", hitpoints = 194.0252, armor = 191.2548, rate = 0.3231426, drain = 15.58567, maxDamage = 505.5446, shieldEfficiency = 0, minDamage = 287.7425, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium, "object/ship/freightermedium.iff")
