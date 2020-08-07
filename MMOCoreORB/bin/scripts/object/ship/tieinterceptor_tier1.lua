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


object_ship_tieinterceptor_tier1 = object_ship_shared_tieinterceptor_tier1:new {

	name = "tieinterceptor_tier1",
	slideFactor = 1.64,
	chassisHitpoints = 240,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 145.0486, armor = 145.1537,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 149.0014, armor = 144.1081, speed = 49.6269, pitch = 21.99977, roll = 27.94775, yaw = 17.88688, acceleration = 11.12594, rollRate = 49.54115, pitchRate = 46.01398, deceleration = 8.294804, yawRate = 37.75788,},
	shield_0 = { name = "shd_generic", hitpoints = 148.0725, armor = 146.4354, regen = 2.493789, front = 508.5944, back = 498.9008,},
	armor_0 = { name = "arm_generic", hitpoints = 308.1021, armor = 319.3904,},
	armor_1 = { name = "arm_generic", hitpoints = 314.58, armor = 314.3841,},
	capacitor = { name = "cap_generic", hitpoints = 149.0734, armor = 146.9709, rechargeRate = 99.9427, energy = 4758.062,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 145.2646, armor = 144.3096, rate = 0.751349, drain = 0.9944501, maxDamage = 39.22985, shieldEfficiency = 0.5340895, minDamage = 29.18281, ammo = 0, ammo_type = 0, armorEfficiency = 0.5382541,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor_tier1, "object/ship/tieinterceptor_tier1.iff")
