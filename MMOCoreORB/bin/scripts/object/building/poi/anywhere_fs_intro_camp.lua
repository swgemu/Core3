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


object_building_poi_anywhere_fs_intro_camp = object_building_poi_shared_anywhere_fs_intro_camp:new {
	childObjects = {
		{templateFile = "object/static/structure/tatooine/tent_house_tatooine_style_01.iff", x = 0, z = 0, y = 0, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/general/campfire_smoldering.iff", x = 0.2, z = 0, y = -6.5, ox = 0, oy = 0, oz = 0, ow = 0, cellid = -1, containmentType = -1},
		{templateFile = "object/static/particle/pt_campfire_s01.iff", x = 0.2, z = 0, y = -6.5, ox = 0, oy = 0, oz = 0, ow = 0, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/tatooine/debris_tatt_crate_1.iff", x = -3.85, z = 0, y = -1.82, ox = 0, oy = -0.214248, oz = 0, ow = 0.976779, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/tatooine/debris_tatt_crate_metal_1.iff", x = -3.46, z = 0, y = -2.45, ox = 0, oy = -0.214248, oz = 0, ow = 0.976779, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/tatooine/debris_tatt_drum_dented_1.iff", x = -4.4084, z = 0, y = -0.827468, ox = 0, oy = -0.214248, oz = 0, ow = 0.976779, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s1.iff", x = -1.75, z = 0, y = -6.75, ox = 0, oy = 0.801575, oz = 0, ow = 0.597895, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s1.iff", x = -1, z = 0, y = -5, ox = 0, oy = 0.938289, oz = 0, ow = 0.345852, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s1.iff", x = 3, z = 0, y = -6.75, ox = 0, oy = 0.787299, oz = 0, ow = -0.616572, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/general/camp_cot_s01.iff", x = -0.018, z = 0, y = 1.9, ox = 0, oy = 0.010666, oz = 0, ow = -0.999943, cellid = -1, containmentType = -1},
		{templateFile = "object/static/structure/general/trash_pile_s01.iff", x = 3.78975, z = 0, y = -2.74693, ox = 0, oy = 0.010666, oz = 0, ow = -0.999943, cellid = -1, containmentType = -1},
	}
}

ObjectTemplates:addTemplate(object_building_poi_anywhere_fs_intro_camp, "object/building/poi/anywhere_fs_intro_camp.iff")
