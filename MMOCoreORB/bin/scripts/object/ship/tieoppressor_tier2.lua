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


object_ship_tieoppressor_tier2 = object_ship_shared_tieoppressor_tier2:new {

	name = "tieoppressor_tier2",
	slideFactor = 1.72,
	chassisHitpoints = 660,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 479.6501, armor = 478.1168,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 473.6155, armor = 480.5413, speed = 42.23869, pitch = 22.76208, roll = 28.98426, yaw = 18.78856, acceleration = 10.06428, rollRate = 53.02531, pitchRate = 45.45, deceleration = 8.833038, yawRate = 38.32977,},
	shield_0 = { name = "shd_generic", hitpoints = 473.4137, armor = 480.0133, regen = 5.861126, front = 1977.153, back = 1943.637,},
	armor_0 = { name = "arm_generic", hitpoints = 1035.447, armor = 1034.058,},
	armor_1 = { name = "arm_generic", hitpoints = 1027.529, armor = 1015.892,},
	capacitor = { name = "cap_generic", hitpoints = 493.9452, armor = 487.1746, rechargeRate = 96.7402, energy = 4995.215,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 483.3521, armor = 475.7401, rate = 0.7464462, drain = 0.9510444, maxDamage = 84.9682, shieldEfficiency = 0.5382282, minDamage = 60.0714, ammo = 0, ammo_type = 0, armorEfficiency = 0.5448152,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 479.2368, armor = 487.6568, rate = 2.914009, drain = 0.9516227, maxDamage = 257.753, shieldEfficiency = 0.7462956, minDamage = 122.6056, ammo = 4, ammo_type = 17, armorEfficiency = 0.7406248,},
}

ObjectTemplates:addTemplate(object_ship_tieoppressor_tier2, "object/ship/tieoppressor_tier2.iff")
