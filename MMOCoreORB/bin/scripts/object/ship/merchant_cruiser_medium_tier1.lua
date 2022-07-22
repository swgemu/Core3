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


object_ship_merchant_cruiser_medium_tier1 = object_ship_shared_merchant_cruiser_medium_tier1:new {

	name = "merchant_cruiser_medium_tier1",
	slideFactor = 1.76,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1445.383, armor = 1470.126,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1465.652, armor = 1480.709, speed = 41.96306, pitch = 22.41469, roll = 27.64444, yaw = 17.39014, acceleration = 9.87539, rollRate = 49.94206, pitchRate = 45.51489, deceleration = 8.494962, yawRate = 37.27012,},
	shield_0 = { name = "shd_generic", hitpoints = 1453.133, armor = 1454.246, regen = 4.385069, front = 5971.663, back = 5844.413,},
	armor_0 = { name = "arm_generic", hitpoints = 3182.048, armor = 3076.015,},
	armor_1 = { name = "arm_generic", hitpoints = 3070.428, armor = 3091.755,},
	capacitor = { name = "cap_generic", hitpoints = 1466.258, armor = 1471.841, rechargeRate = 96.07048, energy = 4961.954,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 1447.478, armor = 1441.749, rate = 0.7581113, drain = 0.9551668, maxDamage = 97.09477, shieldEfficiency = 0.542008, minDamage = 74.20399, ammo = 0, ammo_type = 0, armorEfficiency = 0.5409201,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 1447.209, armor = 1485.542, rate = 0.7794355, drain = 0.9874575, maxDamage = 96.81009, shieldEfficiency = 0.5442611, minDamage = 74.81734, ammo = 0, ammo_type = 0, armorEfficiency = 0.5522206,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 1456.422, armor = 1461.185, rate = 0.7760149, drain = 0.9801174, maxDamage = 95.03839, shieldEfficiency = 0.5336819, minDamage = 73.72643, ammo = 0, ammo_type = 0, armorEfficiency = 0.5483275,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1468.77, armor = 1466.743, rate = 2.896584, drain = 0.9815826, maxDamage = 288.4673, shieldEfficiency = 0.7485359, minDamage = 143.9839, ammo = 5, ammo_type = 16, armorEfficiency = 0.7431346,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1427.075, armor = 1426.033, rate = 2.936557, drain = 0.9707726, maxDamage = 292.2596, shieldEfficiency = 0.7199729, minDamage = 146.2125, ammo = 5, ammo_type = 16, armorEfficiency = 0.7229126,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier1, "object/ship/merchant_cruiser_medium_tier1.iff")
