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


object_ship_blacksun_transport_tier1 = object_ship_shared_blacksun_transport_tier1:new {

	name = "blacksun_transport_tier1",
	slideFactor = 1.83,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 290.749, armor = 293.694,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 289.707, armor = 285.7285, speed = 40.32232, pitch = 22.19708, roll = 28.01435, yaw = 17.94019, acceleration = 10.15108, rollRate = 51.65462, pitchRate = 44.37415, deceleration = 8.682545, yawRate = 38.10884,},
	shield_0 = { name = "shd_generic", hitpoints = 292.2346, armor = 287.1302, regen = 2.856079, front = 1780.152, back = 1748.299,},
	armor_0 = { name = "arm_generic", hitpoints = 918.0464, armor = 917.3929,},
	armor_1 = { name = "arm_generic", hitpoints = 927.7165, armor = 915.3695,},
	capacitor = { name = "cap_generic", hitpoints = 297.281, armor = 291.5778, rechargeRate = 96.88525, energy = 4803.332,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_transport_tier1, "object/ship/blacksun_transport_tier1.iff")
