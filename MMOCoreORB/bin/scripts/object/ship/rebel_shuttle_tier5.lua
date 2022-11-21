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


object_ship_rebel_shuttle_tier5 = object_ship_shared_rebel_shuttle_tier5:new {

	name = "rebel_shuttle_tier5",
	slideFactor = 1.74,
	chassisHitpoints = 7372.8,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6340.857, armor = 6331.828,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6184.335, armor = 6210.672, speed = 45.46261, pitch = 24.91576, roll = 31.39679, yaw = 20.04262, acceleration = 11.19291, rollRate = 58.5865, pitchRate = 50.57949, deceleration = 9.74021, yawRate = 41.06018,},
	shield_0 = { name = "shd_generic", hitpoints = 6160.398, armor = 6158.439, regen = 44.39045, front = 48433, back = 49931.71,},
	armor_0 = { name = "arm_generic", hitpoints = 19982.21, armor = 19579.73,},
	armor_1 = { name = "arm_generic", hitpoints = 19645.79, armor = 19904.86,},
	capacitor = { name = "cap_generic", hitpoints = 6257.294, armor = 6177.662, rechargeRate = 98.34201, energy = 4831.732,},
}

ObjectTemplates:addTemplate(object_ship_rebel_shuttle_tier5, "object/ship/rebel_shuttle_tier5.iff")
