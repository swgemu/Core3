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


object_building_naboo_cloning_facility_naboo = object_building_naboo_shared_cloning_facility_naboo:new {
	planetMapCategory = "cloningfacility",
	facilityType = CLONER_STANDARD,

	skillMods = {
		{"private_medical_rating", 100}
	},

	childObjects = {
		{templateFile = "object/tangible/terminal/terminal_cloning.iff", x = 1, z = -0.05, y = 2.5, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_cloning.iff", x = 1, z = -0.05, y = -1.35, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_insurance.iff", x = 8, z = -0.05, y = 3, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1}
	},

	spawningPoints = {
		{ x = -16.6989, z = -4.29167, y = -10.4941, ow = 0.704268, ox = 0, oz = 0, oy = 0.709934, cellid = 4 },
		{ x = -16.5557, z = -4.29167, y = -14.1447, ow = 0.737658, ox = 0, oz = 0, oy = 0.675174, cellid = 4 },
		{ x = 16.3793, z = -4.29167, y = -14.1493, ow = 0.719682, ox = 0, oz = 0, oy = -0.694303, cellid = 4 },
		{ x = 16.4255, z = -4.29167, y = -10.5014, ow = 0.707601, ox = -0, oz = 0, oy = -0.706612, cellid = 4 },
		{ x = 6.38176, z = -4.79167, y = 0.603229, ow = -0.00984072, ox = 0, oz = 0, oy = 0.999952, cellid = 4 },
		{ x = 1.74664, z = -4.79167, y = 0.582775, ow = 0.0143216, ox = 0, oz = 0, oy = 0.999897, cellid = 4 },
		{ x = -2.76574, z = -4.79167, y = 0.657588, ow = -0.0511122, ox = 0, oz = 0, oy = 0.998693, cellid = 4 }
	}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING
}

ObjectTemplates:addTemplate(object_building_naboo_cloning_facility_naboo, "object/building/naboo/cloning_facility_naboo.iff")
