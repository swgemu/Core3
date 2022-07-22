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


object_ship_player_player_basic_tiefighter = object_ship_player_shared_player_basic_tiefighter:new {

	name = "player_basic_tiefighter",
	slideFactor = 1.95,
	chassisHitpoints = 400,
	chassisMass = 5000,
	reactor = { name = "rct_tiefighter_basic", hitpoints = 193.3756, armor = 97.10411,},
	engine = { name = "eng_tiefighter_basic", hitpoints = 197.5299, armor = 97.35545, speed = 49.00538, pitch = 47.90972, roll = 51.01502, yaw = 47.31527, acceleration = 15.51835, rollRate = 75.38376, pitchRate = 71.14635, deceleration = 13.36026, yawRate = 71.63885,},
	armor_0 = { name = "armor_tiefighter_basic", hitpoints = 632.2285, armor = 640.0355,},
	armor_1 = { name = "armor_tiefighter_basic", hitpoints = 649.0071, armor = 635.1793,},
	capacitor = { name = "cap_tiefighter_basic", hitpoints = 196.3024, armor = 97.62894, rechargeRate = 19.30076, energy = 498.3523,},
	droid_interface = { name = "ddi_tiefighter_basic", hitpoints = 198.608, armor = 97.3598,},
	weapon_0 = { name = "wpn_tiefighter_basic", hitpoints = 192.3501, armor = 99.45217, rate = 0.3369635, drain = 16.91832, maxDamage = 401.2384, shieldEfficiency = 0, minDamage = 327.9787, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_basic_tiefighter, "object/ship/player/player_basic_tiefighter.iff")
