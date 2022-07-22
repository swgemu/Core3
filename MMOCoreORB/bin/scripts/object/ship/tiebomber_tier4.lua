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


object_ship_tiebomber_tier4 = object_ship_shared_tiebomber_tier4:new {

	name = "tiebomber_tier4",
	slideFactor = 1.66,
	chassisHitpoints = 2880,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1983.358, armor = 2013.173,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 2027.378, armor = 1989.282, speed = 45.13489, pitch = 24.20847, roll = 30.88486, yaw = 19.12486, acceleration = 11.0826, rollRate = 55.26555, pitchRate = 48.87264, deceleration = 9.055072, yawRate = 40.83818,},
	shield_0 = { name = "shd_generic", hitpoints = 2008.254, armor = 1986.169, regen = 10.9901, front = 5942.106, back = 6162.866,},
	armor_0 = { name = "arm_generic", hitpoints = 6400.718, armor = 6458.562,},
	armor_1 = { name = "arm_generic", hitpoints = 6535.212, armor = 6516.007,},
	capacitor = { name = "cap_generic", hitpoints = 2048.52, armor = 2008.332, rechargeRate = 99.4261, energy = 4937.034,},
	weapon_0 = { name = "wpn_generic", hitpoints = 2063.514, armor = 1975.186, rate = 0.7669582, drain = 0.9819901, maxDamage = 240.6552, shieldEfficiency = 0.5517358, minDamage = 157.6402, ammo = 0, ammo_type = 0, armorEfficiency = 0.543983,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 2049.182, armor = 2052.752, rate = 2.927103, drain = 0.9591691, maxDamage = 742.8419, shieldEfficiency = 0.7427201, minDamage = 314.4598, ammo = 4, ammo_type = 19, armorEfficiency = 0.7217633,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber_tier4, "object/ship/tiebomber_tier4.iff")
