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


object_ship_player_player_yt1300 = object_ship_player_shared_player_yt1300:new {

	name = "player_yt1300",
	slideFactor = 1.85,
	chassisHitpoints = 5000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 391.9558, armor = 381.4522,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.82562, armor = 98.25301, speed = 63.97898, pitch = 52.14573, roll = 52.79561, yaw = 20.14787, acceleration = 14.34252, rollRate = 81.50523, pitchRate = 74.24856, deceleration = 13.13524, yawRate = 36.47185,},
	shield_0 = { name = "shd_generic", hitpoints = 396.4766, armor = 477.7777, regen = 2.886155, front = 1573.84, back = 1576.103,},
	armor_0 = { name = "arm_generic", hitpoints = 1050.284, armor = 1075.379,},
	armor_1 = { name = "arm_generic", hitpoints = 1065.105, armor = 1082.513,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.81905, energy = 1104.78,},
	booster = { name = "bst_generic", hitpoints = 19.69748, armor = 19.60778, energy = 99.83335, acceleration = 19.59531, speed = 14.5217, energyUsage = 9.508913, rechargeRate = 4.955956,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 195.9011, armor = 190.4336, rate = 0.3411672, drain = 23.1761, maxDamage = 1473.524, shieldEfficiency = 0, minDamage = 723.5058, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 193.3382, armor = 194.2152, rate = 0.3371132, drain = 23.31378, maxDamage = 966.0139, shieldEfficiency = 0, minDamage = 597.9089, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.89749, armor = 19.02803, rate = 5.740155, drain = 23.16122, maxDamage = 22.6369, shieldEfficiency = 0, minDamage = 22.91667, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 19.2737, armor = 19.12519, rate = 0.3286487, drain = 23.17929, maxDamage = 22.90508, shieldEfficiency = 0, minDamage = 23.23277, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	lots = 4,
}

ObjectTemplates:addTemplate(object_ship_player_player_yt1300, "object/ship/player/player_yt1300.iff")
