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


object_ship_decimator_tier2 = object_ship_shared_decimator_tier2:new {

	name = "decimator_tier2",
	slideFactor = 1.69,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 897.9018, armor = 870.0106,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 868.9688, armor = 863.532, speed = 42.38042, pitch = 23.46791, roll = 28.33645, yaw = 18.83926, acceleration = 10.22522, rollRate = 51.52802, pitchRate = 45.44442, deceleration = 8.878887, yawRate = 38.38667,},
	shield_0 = { name = "shd_generic", hitpoints = 887.1408, armor = 865.2653, regen = 10.57798, front = 3598.504, back = 3476.511,},
	armor_0 = { name = "arm_generic", hitpoints = 1894.692, armor = 1850.838,},
	armor_1 = { name = "arm_generic", hitpoints = 1883.491, armor = 1842.881,},
	capacitor = { name = "cap_generic", hitpoints = 882.9471, armor = 898.1904, rechargeRate = 98.08932, energy = 4779.848,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 875.2137, armor = 881.3979, rate = 0.7530142, drain = 0.9755751, maxDamage = 172.6387, shieldEfficiency = 0.5380121, minDamage = 124.9994, ammo = 0, ammo_type = 0, armorEfficiency = 0.5538242,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 855.2119, armor = 860.4954, rate = 0.7594153, drain = 0.9518055, maxDamage = 170.8589, shieldEfficiency = 0.5371149, minDamage = 125.3719, ammo = 0, ammo_type = 0, armorEfficiency = 0.5377072,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 889.483, armor = 855.2405, rate = 2.972251, drain = 0.9908383, maxDamage = 503.2935, shieldEfficiency = 0.7167242, minDamage = 244.264, ammo = 5, ammo_type = 17, armorEfficiency = 0.7213659,},
}

ObjectTemplates:addTemplate(object_ship_decimator_tier2, "object/ship/decimator_tier2.iff")
