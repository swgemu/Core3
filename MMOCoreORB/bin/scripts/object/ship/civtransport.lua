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


object_ship_civtransport = object_ship_shared_civtransport:new {

	name = "civtransport",
	slideFactor = 1.65,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.2669, armor = 96.76806,},
	engine = { name = "eng_generic", hitpoints = 95.75083, armor = 99.19796, speed = 28.52241, pitch = 14.16125, roll = 13.79562, yaw = 13.74818, acceleration = 24.91928, rollRate = 20.83739, pitchRate = 21.09915, deceleration = 22.03843, yawRate = 20.77456,},
	shield_0 = { name = "shd_generic", hitpoints = 195.4382, armor = 198.9861, regen = 4.911304, front = 198.9159, back = 190.0849,},
	armor_0 = { name = "arm_generic", hitpoints = 191.1193, armor = 191.4716,},
	armor_1 = { name = "arm_generic", hitpoints = 192.5262, armor = 197.3831,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 6.270225, energy = 156.2427,},
	weapon_0 = { name = "wpn_generic", hitpoints = 196.3548, armor = 194.5331, rate = 0.06330398, drain = 2.97235, maxDamage = 238.8745, shieldEfficiency = 0, minDamage = 115.6358, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_civtransport, "object/ship/civtransport.iff")
