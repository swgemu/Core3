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


object_tangible_event_perk_audience_seating = object_tangible_poi_base_shared_poi_base:new {
	invisible = 1,

	gameObjectType = 16410, -- Event Perk

	dataObjectComponent = "EventPerkDataComponent",
	attributeListComponent = "EventPerkAttributeListComponent",
	objectMenuComponent = "EventPerkMenuComponent",

	childObjects = {
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -4.53, z = 0, y = 2.50, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -3.47, z = 0, y = 2.48, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -1.36, z = 0, y = 2.48, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -2.41, z = 0, y = 2.48, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -1.42, z = 0, y = 0.81, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -2.46, z = 0, y = 0.81, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -3.52, z = 0, y = 0.80, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -4.59, z = 0, y = 0.82, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -1.53, z = 0, y = -2.47, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -3.39, z = 0, y = -2.46, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 4.61, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 2.51, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -4.42, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -2.50, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -1.52, z = 0, y = -0.85, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -3.39, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 1.45, z = 0, y = -0.81, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 3.57, z = 0, y = -0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -4.42, z = 0, y = -2.49, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = -2.51, z = 0, y = -2.45, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 2.47, z = 0, y = -2.49, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 4.58, z = 0, y = -2.48, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 3.53, z = 0, y = -2.49, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 1.41, z = 0, y = -2.47, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 4.51, z = 0, y = 0.81, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 2.40, z = 0, y = 0.80, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 3.46, z = 0, y = 0.81, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 1.34, z = 0, y = 0.83, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 1.32, z = 0, y = 2.51, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 3.44, z = 0, y = 2.49, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 4.49, z = 0, y = 2.50, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{templateFile = "object/tangible/furniture/all/frn_all_chair_wooden_s2.iff", x = 2.38, z = 0, y = 2.49, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
	},

}

ObjectTemplates:addTemplate(object_tangible_event_perk_audience_seating, "object/tangible/event_perk/audience_seating.iff")
