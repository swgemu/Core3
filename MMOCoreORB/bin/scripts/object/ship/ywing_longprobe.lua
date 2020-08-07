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


object_ship_ywing_longprobe = object_ship_shared_ywing_longprobe:new {

	name = "ywing_longprobe",
	slideFactor = 1.88,
	chassisHitpoints = 339,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.06461, armor = 96.93682,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.19398, armor = 99.32206, speed = 32.6059, pitch = 16.41687, roll = 16.63999, yaw = 16.08926, acceleration = 8.088574, rollRate = 30.56332, pitchRate = 30.59995, deceleration = 9.202122, yawRate = 31.87159,},
	shield_0 = { name = "shd_generic", hitpoints = 380.4309, armor = 477.075, regen = 4.839793, front = 498.6812, back = 581.5155,},
	armor_0 = { name = "arm_generic", hitpoints = 587.7935, armor = 585.7261,},
	armor_1 = { name = "arm_generic", hitpoints = 578.1149, armor = 577.8791,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.63549, energy = 565.3741,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 196.0749, armor = 191.3092, rate = 0.3344227, drain = 22.84121, maxDamage = 314.7901, shieldEfficiency = 0, minDamage = 212.4149, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.2542, armor = 196.5682, rate = 0.3308832, drain = 23.32487, maxDamage = 22.67394, shieldEfficiency = 0, minDamage = 22.81719, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_ywing_longprobe, "object/ship/ywing_longprobe.iff")
