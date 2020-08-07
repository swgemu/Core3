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


object_ship_freightermedium_tier5 = object_ship_shared_freightermedium_tier5:new {

	name = "freightermedium_tier5",
	slideFactor = 1.87,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6189.055, armor = 6220.01,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6361.733, armor = 6205.172, speed = 47.24221, pitch = 25.81544, roll = 31.50323, yaw = 19.8544, acceleration = 11.11803, rollRate = 57.24327, pitchRate = 51.82141, deceleration = 9.483819, yawRate = 42.74206,},
	shield_0 = { name = "shd_generic", hitpoints = 6230.504, armor = 6288.122, regen = 27.95188, front = 48687.83, back = 49502.69,},
	armor_0 = { name = "arm_generic", hitpoints = 27046.54, armor = 26806.87,},
	armor_1 = { name = "arm_generic", hitpoints = 26519.48, armor = 26161.05,},
	capacitor = { name = "cap_generic", hitpoints = 6133.227, armor = 6225.586, rechargeRate = 97.56967, energy = 4809.417,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium_tier5, "object/ship/freightermedium_tier5.iff")
