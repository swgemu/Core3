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


object_ship_player_player_xwing = object_ship_player_shared_player_xwing:new {

	name = "player_xwing",
	slideFactor = 1.95,
	chassisHitpoints = 6000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 3162.779, armor = 1577.898,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3100.646, armor = 1547.045, speed = 88.89402, pitch = 77.74859, roll = 76.08578, yaw = 74.17932, acceleration = 16.41803, rollRate = 70.87788, pitchRate = 70.40349, deceleration = 14.86729, yawRate = 71.43987,},
	shield_0 = { name = "shd_generic", hitpoints = 3063.218, armor = 1535.663, regen = 29.77072, front = 9863.458, back = 9636.04,},
	armor_0 = { name = "arm_generic", hitpoints = 7992.892, armor = 7736.91,},
	armor_1 = { name = "arm_generic", hitpoints = 7840.671, armor = 7766.51,},
	capacitor = { name = "cap_generic", hitpoints = 3077.529, armor = 1565.867, rechargeRate = 58.67234, energy = 1923.184,},
	booster = { name = "bst_generic", hitpoints = 899.4767, armor = 879.5552, energy = 2385.906, acceleration = 19.44374, speed = 39.82451, energyUsage = 9.810509, rechargeRate = 58.34419,},
	droid_interface = { name = "ddi_generic", hitpoints = 867.1381, armor = 874.595,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 3107.491, armor = 1575.777, rate = 0.3906129, drain = 19.53834, maxDamage = 5229.694, shieldEfficiency = 0, minDamage = 3970.184, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 3146.795, armor = 1583.318, rate = 0.3987256, drain = 19.05866, maxDamage = 5288.59, shieldEfficiency = 0, minDamage = 3967.771, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 3062.799, armor = 1518.981, rate = 0.3114218, drain = 28.79232, maxDamage = 5132.656, shieldEfficiency = 0.870634, minDamage = 3871.577, ammo = 50, ammo_type = 5, armorEfficiency = 0.2198195,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 243.0028, armor = 247.8218, rate = 0.09622593, drain = 23.41949, maxDamage = 97.17074, shieldEfficiency = 0, minDamage = 24.89145, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_xwing, "object/ship/player/player_xwing.iff")
