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


object_ship_freightermedium_tier2 = object_ship_shared_freightermedium_tier2:new {

	name = "freightermedium_tier2",
	slideFactor = 1.87,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 872.4962, armor = 882.7373,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 881.1819, armor = 884.4622, speed = 42.83303, pitch = 23.27704, roll = 29.17179, yaw = 18.30495, acceleration = 10.18387, rollRate = 52.29356, pitchRate = 45.57418, deceleration = 8.636573, yawRate = 38.46419,},
	shield_0 = { name = "shd_generic", hitpoints = 867.8511, armor = 888.119, regen = 6.68737, front = 7048.629, back = 6873.239,},
	armor_0 = { name = "arm_generic", hitpoints = 3671.589, armor = 3824.514,},
	armor_1 = { name = "arm_generic", hitpoints = 3733.318, armor = 3730.098,},
	capacitor = { name = "cap_generic", hitpoints = 879.6624, armor = 860.5363, rechargeRate = 95.67747, energy = 4935.059,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium_tier2, "object/ship/freightermedium_tier2.iff")
