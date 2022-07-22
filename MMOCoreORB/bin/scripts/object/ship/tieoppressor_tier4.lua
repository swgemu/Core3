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


object_ship_tieoppressor_tier4 = object_ship_shared_tieoppressor_tier4:new {

	name = "tieoppressor_tier4",
	slideFactor = 1.72,
	chassisHitpoints = 2112,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2248.993, armor = 2186.408,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 2186.386, armor = 2271.765, speed = 45.87213, pitch = 24.32952, roll = 29.96857, yaw = 19.63226, acceleration = 10.63307, rollRate = 54.93143, pitchRate = 48.96416, deceleration = 9.472248, yawRate = 40.7995,},
	shield_0 = { name = "shd_generic", hitpoints = 2232.868, armor = 2253.602, regen = 16.24959, front = 8826.264, back = 9007.36,},
	armor_0 = { name = "arm_generic", hitpoints = 4763.34, armor = 4853.612,},
	armor_1 = { name = "arm_generic", hitpoints = 4822.766, armor = 4624.587,},
	capacitor = { name = "cap_generic", hitpoints = 2182.337, armor = 2187.385, rechargeRate = 95.71564, energy = 4752.665,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 2228.064, armor = 2259.219, rate = 0.7427525, drain = 0.9621342, maxDamage = 245.4486, shieldEfficiency = 0.5467485, minDamage = 163.0472, ammo = 0, ammo_type = 0, armorEfficiency = 0.5530345,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 2276.378, armor = 2252.515, rate = 2.871072, drain = 0.9509214, maxDamage = 756.7805, shieldEfficiency = 0.7338705, minDamage = 324.7253, ammo = 4, ammo_type = 19, armorEfficiency = 0.7496052,},
}

ObjectTemplates:addTemplate(object_ship_tieoppressor_tier4, "object/ship/tieoppressor_tier4.iff")
