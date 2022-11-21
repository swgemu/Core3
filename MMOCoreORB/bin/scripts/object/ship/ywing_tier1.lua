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


object_ship_ywing_tier1 = object_ship_shared_ywing_tier1:new {

	name = "ywing_tier1",
	slideFactor = 1.77,
	chassisHitpoints = 240,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 148.8149, armor = 144.3276,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 146.8733, armor = 145.1711, speed = 41.31506, pitch = 22.75728, roll = 28.0798, yaw = 17.73602, acceleration = 9.768072, rollRate = 49.58394, pitchRate = 46.13453, deceleration = 8.649048, yawRate = 37.67102,},
	shield_0 = { name = "shd_generic", hitpoints = 148.9213, armor = 147.1307, regen = 2.916567, front = 574.4744, back = 591.4418,},
	armor_0 = { name = "arm_generic", hitpoints = 344.9767, armor = 337.9284,},
	armor_1 = { name = "arm_generic", hitpoints = 342.0909, armor = 340.5414,},
	capacitor = { name = "cap_generic", hitpoints = 147.8608, armor = 144.6162, rechargeRate = 99.54704, energy = 4830.858,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 145.613, armor = 149.8029, rate = 0.7519081, drain = 0.9921293, maxDamage = 38.35658, shieldEfficiency = 0.5466204, minDamage = 29.02275, ammo = 0, ammo_type = 0, armorEfficiency = 0.5562694,},
	weapon_1 = { name = "wpn_slayn_ioncannon", hitpoints = 147.8979, armor = 145.0752, rate = 0.772851, drain = 0.957451, maxDamage = 38.80447, shieldEfficiency = 0.5424306, minDamage = 29.39395, ammo = 0, ammo_type = 0, armorEfficiency = 0.5593872,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 143.6828, armor = 146.243, rate = 2.962385, drain = 0.9673574, maxDamage = 119.4836, shieldEfficiency = 0.7255929, minDamage = 58.56344, ammo = 4, ammo_type = 16, armorEfficiency = 0.7145271,},
}

ObjectTemplates:addTemplate(object_ship_ywing_tier1, "object/ship/ywing_tier1.iff")
