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


object_ship_player_player_tiefighter = object_ship_player_shared_player_tiefighter:new {

	name = "player_tiefighter",
	slideFactor = 1.78,
	chassisHitpoints = 1350,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 293.8558, armor = 293.7918,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 299.4926, armor = 291.9119, speed = 46.92483, pitch = 57.79565, roll = 65.51756, yaw = 39.94093, acceleration = 16.51487, rollRate = 81.69034, pitchRate = 79.91472, deceleration = 14.73175, yawRate = 71.56434,},
	shield_0 = { name = "shd_generic", hitpoints = 294.1006, armor = 299.7027, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 389.843, armor = 391.1746,},
	armor_1 = { name = "arm_generic", hitpoints = 390.5956, armor = 399.9057,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 46.7646, energy = 794.7725,},
	weapon_0 = { name = "wpn_generic", hitpoints = 191.7255, armor = 190.2055, rate = 0.2780028, drain = 26.71595, maxDamage = 563.3237, shieldEfficiency = 0, minDamage = 491.7242, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 199.22, armor = 190.3089, rate = 8.864588, drain = 30.89153, maxDamage = 800.2283, shieldEfficiency = 0.7719823, minDamage = 499.0948, ammo = 8, ammo_type = 2, armorEfficiency = 0.5506808,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 239.3105, armor = 242.0033, rate = 0.09992722, drain = 22.86495, maxDamage = 95.85281, shieldEfficiency = 0, minDamage = 24.41938, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tiefighter, "object/ship/player/player_tiefighter.iff")
