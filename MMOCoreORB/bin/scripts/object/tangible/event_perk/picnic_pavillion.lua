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


object_tangible_event_perk_picnic_pavillion = object_tangible_poi_base_shared_poi_base:new {
	invisible = 1,

	gameObjectType = 16410, -- Event Perk

	dataObjectComponent = "EventPerkDataComponent",
	attributeListComponent = "EventPerkAttributeListComponent",
	objectMenuComponent = "EventPerkMenuComponent",

	childObjects = {
		{ templateFile = "object/tangible/furniture/modern/dining_table_modern_style_01.iff", x = 0.0709, z = -0.4487, y = 0.0219, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/camp/camp_pavilion_s1.iff", x = -0.2466, z = -0.4487, y = -0.0052, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = -0.7615, z = -0.33, y = 2.1514, ow = 0.01079, ox = 0, oy = 0.99994, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = 2.5379, z = -0.33, y = 2.2055, ow = 0.00421, ox = 0, oy = 0.99999, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = 0.8275, z = -0.33, y = -1.9991, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = -0.7605, z = -0.33, y = -2.0277, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = -2.4825, z = -0.33, y = 2.1206, ow = 0.01079, ox = 0, oy = 0.99994, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = -4.5630, z = -0.33, y = 0.0507, ow = 0.71091, ox = 0, oy = 0.70328, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = -2.4420, z = -0.33, y = -2.0343, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = 0.9603, z = -0.33, y = 2.1823, ow = 0.01579, ox = 0, oy = 0.99988, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = 4.7267, z = -0.33, y = -0.0060, ow = 0.70739, ox = 0, oy = -0.70683, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/modern/chair_modern_style_01.iff", x = 2.3935, z = -0.33, y = -1.9828, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s03.iff", x = 0.0612, z = 0.5631, y = -0.0549391, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s03.iff", x = 1.7093, z = 0.5632, y = -0.0922826, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s03.iff", x = -1.5543, z = 0.5316, y = -0.102965, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", x = -5.0676, z = -0.4487, y = 5.7276, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", x = 4.6713, z = -0.4487, y = -5.8555, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", x = 4.8673, z = -0.4487, y = 5.9226, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff", x = -5.2473, z = -0.4487, y = -6.0606, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
	},
}

ObjectTemplates:addTemplate(object_tangible_event_perk_picnic_pavillion, "object/tangible/event_perk/picnic_pavillion.iff")
