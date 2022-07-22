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


object_ship_spacestation_imperial = object_ship_shared_spacestation_imperial:new {

	name = "spacestation_imperial",
	customName = "ImperialStation",
	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 4784.225, armor = 1987.221,},
	shield_0 = { name = "shd_generic", hitpoints = 9607.81, armor = 2988.824, regen = 49.31623, front = 5947.377, back = 5963.385,},
	shield_1 = { name = "shd_generic", hitpoints = 4789.996, armor = 2978.286, regen = 38.73238, front = 2996.965, back = 2987.196,},
	armor_0 = { name = "arm_generic", hitpoints = 4885.021, armor = 4808.957,},
	armor_1 = { name = "arm_generic", hitpoints = 4885.804, armor = 4953.121,},
	capacitor = { name = "cap_generic", hitpoints = 4852.163, armor = 961.3992, rechargeRate = 126.975, energy = 2322.189,},
	bridge = { name = "bdg_generic", hitpoints = 1956.12, armor = 1916.21,},
	hangar = { name = "hgr_generic", hitpoints = 1933.855, armor = 1997.672,},
}

ObjectTemplates:addTemplate(object_ship_spacestation_imperial, "object/ship/spacestation_imperial.iff")
