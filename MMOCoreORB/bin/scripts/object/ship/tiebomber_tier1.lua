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


object_ship_tiebomber_tier1 = object_ship_shared_tiebomber_tier1:new {

	name = "tiebomber_tier1",
	slideFactor = 1.66,
	chassisHitpoints = 360,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 148.1184, armor = 146.1306,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 149.6301, armor = 143.0023, speed = 41.339, pitch = 22.75678, roll = 27.36526, yaw = 17.81995, acceleration = 10.10473, rollRate = 52.05822, pitchRate = 45.38196, deceleration = 8.385027, yawRate = 37.27747,},
	shield_0 = { name = "shd_generic", hitpoints = 145.84, armor = 147.7897, regen = 2.20422, front = 445.7551, back = 430.1823,},
	armor_0 = { name = "arm_generic", hitpoints = 472.1407, armor = 460.7245,},
	armor_1 = { name = "arm_generic", hitpoints = 468.8609, armor = 464.8188,},
	capacitor = { name = "cap_generic", hitpoints = 148.0738, armor = 145.788, rechargeRate = 99.35069, energy = 4787.006,},
	weapon_0 = { name = "wpn_generic", hitpoints = 145.6256, armor = 143.784, rate = 0.7518178, drain = 0.9950711, maxDamage = 38.27077, shieldEfficiency = 0.5436019, minDamage = 28.79168, ammo = 0, ammo_type = 0, armorEfficiency = 0.5325789,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 146.3227, armor = 145.9299, rate = 2.863847, drain = 0.9748735, maxDamage = 117.9564, shieldEfficiency = 0.7339752, minDamage = 59.92194, ammo = 4, ammo_type = 16, armorEfficiency = 0.7457716,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber_tier1, "object/ship/tiebomber_tier1.iff")
