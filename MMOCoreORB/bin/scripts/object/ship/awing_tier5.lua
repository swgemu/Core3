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


object_ship_awing_tier5 = object_ship_shared_awing_tier5:new {

	name = "awing_tier5",
	slideFactor = 1.62,
	chassisHitpoints = 2211.84,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2725.246, armor = 2769.615,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2766.59, armor = 2802.299, speed = 51.77354, pitch = 25.56588, roll = 31.99031, yaw = 20.11832, acceleration = 12.08107, rollRate = 58.18108, pitchRate = 50.67995, deceleration = 9.597297, yawRate = 41.3633,},
	shield_0 = { name = "shd_generic", hitpoints = 2773.702, armor = 2796.259, regen = 22.68984, front = 11246.96, back = 11123.93,},
	armor_0 = { name = "arm_generic", hitpoints = 5932.246, armor = 5828.645,},
	armor_1 = { name = "arm_generic", hitpoints = 5944.551, armor = 5953.357,},
	capacitor = { name = "cap_generic", hitpoints = 2798.387, armor = 2744.961, rechargeRate = 96.86231, energy = 4799.315,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 2861.687, armor = 2856.089, rate = 0.7590994, drain = 0.9955612, maxDamage = 319.9776, shieldEfficiency = 0.5573096, minDamage = 204.3969, ammo = 0, ammo_type = 0, armorEfficiency = 0.5349304,},
}

ObjectTemplates:addTemplate(object_ship_awing_tier5, "object/ship/awing_tier5.iff")
