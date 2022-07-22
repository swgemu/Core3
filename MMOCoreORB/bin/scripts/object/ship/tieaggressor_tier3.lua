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


object_ship_tieaggressor_tier3 = object_ship_shared_tieaggressor_tier3:new {

	name = "tieaggressor_tier3",
	slideFactor = 1.68,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1064.584, armor = 1076.519,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 1058.593, armor = 1042.975, speed = 43.19534, pitch = 23.50732, roll = 29.90912, yaw = 18.54581, acceleration = 10.62517, rollRate = 53.10388, pitchRate = 48.7949, deceleration = 8.901814, yawRate = 38.91549,},
	shield_0 = { name = "shd_generic", hitpoints = 1033.965, armor = 1030.795, regen = 8.821575, front = 4216.153, back = 4242.929,},
	armor_0 = { name = "arm_generic", hitpoints = 2296.912, armor = 2284.09,},
	armor_1 = { name = "arm_generic", hitpoints = 2209.783, armor = 2223.774,},
	capacitor = { name = "cap_generic", hitpoints = 1055.522, armor = 1043.349, rechargeRate = 95.26971, energy = 4959.958,},
	weapon_0 = { name = "wpn_generic", hitpoints = 1057.903, armor = 1048.091, rate = 0.7678753, drain = 0.9945723, maxDamage = 173.6017, shieldEfficiency = 0.538106, minDamage = 119.3556, ammo = 0, ammo_type = 0, armorEfficiency = 0.5358519,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 1032.198, armor = 1032.304, rate = 0.7493938, drain = 0.9640223, maxDamage = 173.3327, shieldEfficiency = 0.5517157, minDamage = 119.0821, ammo = 0, ammo_type = 0, armorEfficiency = 0.5415803,},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor_tier3, "object/ship/tieaggressor_tier3.iff")
