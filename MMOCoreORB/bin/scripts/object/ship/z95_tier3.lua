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


object_ship_z95_tier3 = object_ship_shared_z95_tier3:new {

	name = "z95_tier3",
	slideFactor = 1.84,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1033.966, armor = 1047.067,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1072.203, armor = 1037, speed = 48.03896, pitch = 23.45315, roll = 28.90388, yaw = 18.87323, acceleration = 11.31087, rollRate = 52.79303, pitchRate = 48.84452, deceleration = 9.218369, yawRate = 39.26126,},
	shield_0 = { name = "shd_generic", hitpoints = 1057.729, armor = 1051.376, regen = 8.975671, front = 4518.088, back = 4723.153,},
	armor_0 = { name = "arm_generic", hitpoints = 1824.458, armor = 1760.628,},
	armor_1 = { name = "arm_generic", hitpoints = 1809.152, armor = 1819.449,},
	capacitor = { name = "cap_generic", hitpoints = 1055.859, armor = 1047.867, rechargeRate = 98.76589, energy = 4753.983,},
	booster = { name = "bst_generic", hitpoints = 1061.832, armor = 1049.997, energy = 99.38061, acceleration = 19.9793, speed = 14.2694, energyUsage = 9.932022, rechargeRate = 2.996804,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 1070.672, armor = 1067.939, rate = 0.7521697, drain = 0.9776309, maxDamage = 152.2168, shieldEfficiency = 0.5578364, minDamage = 104.865, ammo = 0, ammo_type = 0, armorEfficiency = 0.5396361,},
}

ObjectTemplates:addTemplate(object_ship_z95_tier3, "object/ship/z95_tier3.iff")
