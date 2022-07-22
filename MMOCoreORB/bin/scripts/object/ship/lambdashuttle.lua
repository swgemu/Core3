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


object_ship_lambdashuttle = object_ship_shared_lambdashuttle:new {

	name = "lambdashuttle",
	slideFactor = 2,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.5471, armor = 97.23254,},
	engine = { name = "eng_generic", hitpoints = 97.17748, armor = 96.95702, speed = 34.80483, pitch = 20.16934, roll = 20.80767, yaw = 20.3017, acceleration = 25.37937, rollRate = 41.78279, pitchRate = 42.71752, deceleration = 21.41701, yawRate = 42.11838,},
	shield_0 = { name = "shd_generic", hitpoints = 198.6937, armor = 195.756, regen = 4.830379, front = 670.274, back = 881.0177,},
	armor_0 = { name = "arm_generic", hitpoints = 790.0546, armor = 767.7416,},
	armor_1 = { name = "arm_generic", hitpoints = 792.7666, armor = 787.9952,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 112.5991, energy = 2869.961,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 190.8945, armor = 193.6534, rate = 1.081946, drain = 53.47401, maxDamage = 342.7379, shieldEfficiency = 0, minDamage = 215.1005, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 197.8365, armor = 198.1094, rate = 1.097557, drain = 52.48106, maxDamage = 51.79254, shieldEfficiency = 0, minDamage = 53.22642, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle, "object/ship/lambdashuttle.iff")
