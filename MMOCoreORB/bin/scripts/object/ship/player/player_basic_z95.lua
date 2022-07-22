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


object_ship_player_player_basic_z95 = object_ship_player_shared_player_basic_z95:new {

	name = "player_basic_z95",
	slideFactor = 1.95,
	chassisHitpoints = 400,
	chassisMass = 5000,
	reactor = { name = "rct_z95_basic", hitpoints = 195.4478, armor = 95.32938,},
	engine = { name = "eng_z95_basic", hitpoints = 191.5668, armor = 97.06787, speed = 41.88384, pitch = 46.81169, roll = 51.68658, yaw = 46.4142, acceleration = 13.31924, rollRate = 75.79074, pitchRate = 69.65774, deceleration = 12.221, yawRate = 71.19044,},
	shield_0 = { name = "shd_z95_basic", hitpoints = 194.8245, armor = 97.74313, regen = 1.941474, front = 296.7128, back = 297.2658,},
	armor_0 = { name = "armor_z95_basic", hitpoints = 244.803, armor = 241.0139,},
	armor_1 = { name = "armor_z95_basic", hitpoints = 244.9245, armor = 245.6187,},
	capacitor = { name = "cap_z95_basic", hitpoints = 191.4282, armor = 97.19357, rechargeRate = 19.43088, energy = 487.1414,},
	droid_interface = { name = "ddi_z95_basic", hitpoints = 197.8011, armor = 96.56534,},
	weapon_0 = { name = "wpn_z95_basic", hitpoints = 197.299, armor = 96.90126, rate = 0.3433608, drain = 16.95366, maxDamage = 402.8612, shieldEfficiency = 0, minDamage = 324.0421, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_basic_z95, "object/ship/player/player_basic_z95.iff")
