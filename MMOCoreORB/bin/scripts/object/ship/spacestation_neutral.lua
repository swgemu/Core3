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


object_ship_spacestation_neutral = object_ship_shared_spacestation_neutral:new {

	name = "spacestation_neutral",
	customName = "NeutralStation",
	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 4966.639, armor = 1916.958,},
	shield_0 = { name = "shd_generic", hitpoints = 9612.102, armor = 2876.292, regen = 49.71952, front = 5983.614, back = 5995.161,},
	shield_1 = { name = "shd_generic", hitpoints = 4842.518, armor = 2969.425, regen = 39.20972, front = 2873.469, back = 2937.772,},
	armor_0 = { name = "arm_generic", hitpoints = 4961.945, armor = 4917.142,},
	armor_1 = { name = "arm_generic", hitpoints = 4897.431, armor = 4877.487,},
	capacitor = { name = "cap_generic", hitpoints = 4922.489, armor = 954.791, rechargeRate = 123.3029, energy = 2292.475,},
	bridge = { name = "bdg_generic", hitpoints = 1977.12, armor = 1964.19,},
	hangar = { name = "hgr_generic", hitpoints = 1946.25, armor = 1917.841,},
}

ObjectTemplates:addTemplate(object_ship_spacestation_neutral, "object/ship/spacestation_neutral.iff")
