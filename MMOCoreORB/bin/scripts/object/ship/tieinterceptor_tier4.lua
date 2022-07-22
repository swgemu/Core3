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


object_ship_tieinterceptor_tier4 = object_ship_shared_tieinterceptor_tier4:new {

	name = "tieinterceptor_tier4",
	slideFactor = 1.64,
	chassisHitpoints = 1920,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2061.277, armor = 2005.128,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 2002.23, armor = 2029.261, speed = 53.41675, pitch = 24.2585, roll = 29.77986, yaw = 19.93316, acceleration = 12.12503, rollRate = 55.431, pitchRate = 49.57956, deceleration = 9.29399, yawRate = 41.35136,},
	shield_0 = { name = "shd_generic", hitpoints = 1996.129, armor = 2032.772, regen = 12.34225, front = 6890.979, back = 6984.074,},
	armor_0 = { name = "arm_generic", hitpoints = 4416.932, armor = 4259.71,},
	armor_1 = { name = "arm_generic", hitpoints = 4319.618, armor = 4345.869,},
	capacitor = { name = "cap_generic", hitpoints = 2011.961, armor = 1977.397, rechargeRate = 97.69634, energy = 4998.684,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 2019.904, armor = 2027.869, rate = 0.7704326, drain = 0.9965058, maxDamage = 240.2097, shieldEfficiency = 0.5477021, minDamage = 160.2336, ammo = 0, ammo_type = 0, armorEfficiency = 0.5381628,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor_tier4, "object/ship/tieinterceptor_tier4.iff")
