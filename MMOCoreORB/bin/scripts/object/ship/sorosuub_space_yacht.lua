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


object_ship_sorosuub_space_yacht = object_ship_shared_sorosuub_space_yacht:new {

	name = "sorosuub_space_yacht",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 299.9898, armor = 294.2328,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.27848, armor = 95.37285, speed = 44.38988, pitch = 39.74926, roll = 40.97852, yaw = 20.41502, acceleration = 11.74901, rollRate = 60.52201, pitchRate = 60.20116, deceleration = 15.0274, yawRate = 39.64298,},
	shield_0 = { name = "shd_generic", hitpoints = 380.9524, armor = 483.4073, regen = 4.825073, front = 933.3693, back = 964.2253,},
	armor_0 = { name = "arm_generic", hitpoints = 199.7969, armor = 197.0853,},
	armor_1 = { name = "arm_generic", hitpoints = 192.092, armor = 199.5949,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.15288, energy = 492.3197,},
}

ObjectTemplates:addTemplate(object_ship_sorosuub_space_yacht, "object/ship/sorosuub_space_yacht.iff")
