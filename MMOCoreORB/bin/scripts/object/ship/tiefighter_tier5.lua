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


object_ship_tiefighter_tier5 = object_ship_shared_tiefighter_tier5:new {

	name = "tiefighter_tier5",
	slideFactor = 1.85,
	chassisHitpoints = 3686.4,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3027.34, armor = 3150.808,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 3057.009, armor = 3176.463, speed = 46.62571, pitch = 25.47468, roll = 31.84615, yaw = 20.58797, acceleration = 11.13056, rollRate = 56.76321, pitchRate = 50.5124, deceleration = 9.398825, yawRate = 42.48166,},
	shield_0 = { name = "shd_generic", hitpoints = 3146.452, armor = 3096.703, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 10106.6, armor = 9758.436,},
	armor_1 = { name = "arm_generic", hitpoints = 10019.86, armor = 10015.07,},
	capacitor = { name = "cap_generic", hitpoints = 3094.228, armor = 3168.944, rechargeRate = 95.42989, energy = 4796.306,},
	weapon_0 = { name = "wpn_generic", hitpoints = 3031.631, armor = 3124.447, rate = 0.7454476, drain = 0.9835394, maxDamage = 318.6493, shieldEfficiency = 0.5466422, minDamage = 204.2657, ammo = 0, ammo_type = 0, armorEfficiency = 0.5586483,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter_tier5, "object/ship/tiefighter_tier5.iff")
