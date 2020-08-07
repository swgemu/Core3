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


object_ship_blacksun_light_s01 = object_ship_shared_blacksun_light_s01:new {

	name = "blacksun_light_s01",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 293.0975, armor = 299.4683,},
	engine = { name = "eng_generic", hitpoints = 96.34592, armor = 95.92737, speed = 52.97753, pitch = 33.03342, roll = 32.61266, yaw = 32.31016, acceleration = 16.27676, rollRate = 58.24209, pitchRate = 60.85304, deceleration = 8.33995, yawRate = 59.25087,},
	shield_0 = { name = "shd_generic", hitpoints = 391.0511, armor = 494.1241, regen = 4.846959, front = 296.6703, back = 478.2641,},
	armor_0 = { name = "arm_generic", hitpoints = 289.9044, armor = 289.124,},
	armor_1 = { name = "arm_generic", hitpoints = 296.4264, armor = 298.3781,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.81828, energy = 544.4305,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.31518, armor = 19.15918, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_light_s01, "object/ship/blacksun_light_s01.iff")
