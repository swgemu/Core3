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


object_ship_civtaxi = object_ship_shared_civtaxi:new {

	name = "civtaxi",
	slideFactor = 1,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 99.60083, armor = 96.09837,},
	engine = { name = "eng_generic", hitpoints = 95.30785, armor = 99.04864, speed = 47.74995, pitch = 18.47241, roll = 18.502, yaw = 18.34647, acceleration = 42.07823, rollRate = 24.98296, pitchRate = 24.11361, deceleration = 36.44434, yawRate = 24.82035,},
	shield_0 = { name = "shd_generic", hitpoints = 197.4062, armor = 195.3905, regen = 4.865842, front = 198.8916, back = 191.9114,},
	armor_0 = { name = "arm_generic", hitpoints = 198.2755, armor = 196.7783,},
	armor_1 = { name = "arm_generic", hitpoints = 192.4777, armor = 193.1838,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 12.66372, energy = 318.0059,},
	weapon_0 = { name = "wpn_generic", hitpoints = 194.7361, armor = 190.4425, rate = 0.1250509, drain = 5.922734, maxDamage = 248.1281, shieldEfficiency = 0, minDamage = 116.9566, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_civtaxi, "object/ship/civtaxi.iff")
