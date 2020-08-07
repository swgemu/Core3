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


object_ship_tieaggressor_tier4 = object_ship_shared_tieaggressor_tier4:new {

	name = "tieaggressor_tier4",
	slideFactor = 1.68,
	chassisHitpoints = 1920,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1992.998, armor = 1979.088,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 1978.276, armor = 2033.112, speed = 45.2157, pitch = 24.49033, roll = 31.17098, yaw = 19.9629, acceleration = 11.04593, rollRate = 54.17124, pitchRate = 48.04925, deceleration = 9.388854, yawRate = 40.80725,},
	shield_0 = { name = "shd_generic", hitpoints = 1975.327, armor = 2023.242, regen = 14.73946, front = 8197.743, back = 8236.207,},
	armor_0 = { name = "arm_generic", hitpoints = 4323.9, armor = 4212.106,},
	armor_1 = { name = "arm_generic", hitpoints = 4250.348, armor = 4219.185,},
	capacitor = { name = "cap_generic", hitpoints = 1978.768, armor = 2000.312, rechargeRate = 96.32249, energy = 4904.999,},
	weapon_0 = { name = "wpn_generic", hitpoints = 2013.107, armor = 2055.94, rate = 0.7526207, drain = 0.9959937, maxDamage = 269.8314, shieldEfficiency = 0.539197, minDamage = 174.8913, ammo = 0, ammo_type = 0, armorEfficiency = 0.5597892,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 2018.315, armor = 1980.471, rate = 0.757284, drain = 0.9800485, maxDamage = 266.4175, shieldEfficiency = 0.5535061, minDamage = 176.7746, ammo = 0, ammo_type = 0, armorEfficiency = 0.533902,},
}

ObjectTemplates:addTemplate(object_ship_tieaggressor_tier4, "object/ship/tieaggressor_tier4.iff")
