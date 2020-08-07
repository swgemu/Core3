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


object_ship_freightermedium_tier4 = object_ship_shared_freightermedium_tier4:new {

	name = "freightermedium_tier4",
	slideFactor = 1.87,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4084.835, armor = 3979.443,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4129.281, armor = 4065.376, speed = 45.88424, pitch = 24.52582, roll = 29.90043, yaw = 19.41673, acceleration = 11.03108, rollRate = 55.13219, pitchRate = 49.73755, deceleration = 9.485765, yawRate = 41.83672,},
	shield_0 = { name = "shd_generic", hitpoints = 4137.981, armor = 4096.555, regen = 18.69904, front = 31695.53, back = 32133.04,},
	armor_0 = { name = "arm_generic", hitpoints = 17198.76, armor = 17236.55,},
	armor_1 = { name = "arm_generic", hitpoints = 17018.43, armor = 17495.58,},
	capacitor = { name = "cap_generic", hitpoints = 3955.907, armor = 3995.596, rechargeRate = 96.0498, energy = 4787.979,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium_tier4, "object/ship/freightermedium_tier4.iff")
