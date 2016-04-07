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


object_tangible_event_perk_wedding_garden_imperial_large_theater = object_tangible_poi_base_shared_poi_base:new {
	invisible = 1,

	gameObjectType = 16410, -- Event Perk

	dataObjectComponent = "EventPerkDataComponent",
	attributeListComponent = "EventPerkAttributeListComponent",
	objectMenuComponent = "EventPerkMenuComponent",

	childObjects = {
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = 3.84, z = 0, y = -12.53, ow = 0.99076, ox = 0, oy = -0.13563, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -10.25, z = 0, y = -6.01, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -4.44, z = 0, y = -15.1, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -4.4, z = 0, y = -12.27, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -3.71, z = 0, y = 6.65, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 8.74, z = 0, y = -5.78, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 11.38, z = 0, y = 0.06, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 8.81, z = 0, y = 0.19, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -12.9, z = 0, y = 0.62, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 2.2, z = 0, y = -12.29, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 11.34, z = 0, y = -5.83, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -12.99, z = 0, y = -5.78, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 3.21, z = 0, y = 6.63, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 3.23, z = 0, y = 9.04, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -10.1, z = 0, y = 0.62, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = -3.63, z = 0, y = 9.51, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/banner_imperial_style_01.iff", x = 2.19, z = 0, y = -14.89, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -3.86, z = 0, y = 4.69, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -7.19, z = 0, y = -5.94, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 2.3, z = 0, y = -10.42, ow = 0.38268, ox = 0, oy = -0.92388, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 2.31, z = 0, y = -9.23, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 6.82, z = 0, y = -5.95, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -3.87, z = 0, y = -9.28, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -7.15, z = 0, y = 0.22, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 5.64, z = 0, y = 0.22, ow = 0.38268, ox = 0, oy = 0.92388, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -3.83, z = 0, y = -10.35, ow = 0, ox = 0, oy = -1, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 2.33, z = 0, y = 3.54, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 2.32, z = 0, y = 4.69, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -3.83, z = 0, y = 3.55, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 5.63, z = 0, y = -5.94, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -8.34, z = 0, y = 0.24, ow = 0.70711, ox = 0, oy = 0.70711, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 6.84, z = 0, y = 0.24, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = 5.45, z = 0, y = 4.77, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/tangible/furniture/all/frn_all_light_lamp_candlestick_tbl_s02.iff", x = -8.38, z = 0, y = -5.91, ow = 0.38268, ox = 0, oy = 0.92388, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/building/player/city/garden_naboo_lrg_01.iff", x = -0.71, z = 0, y = -2.86, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = 8.76, z = 0, y = 1.69, ow = 0.65018, ox = 0, oy = -0.75978, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = -10.28, z = 0, y = -7.45, ow = 0.77079, ox = 0, oy = 0.63709, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = 4.73, z = 0, y = 6.36, ow = 0.07315, ox = 0, oy = -0.99732, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = -10.02, z = 0, y = 2.33 , ow = 0.67469, ox = 0, oy = 0.7381, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = -5.91, z = 0, y = -12.02, ow = 0.99797, ox = 0, oy = 0.06366, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = 8.81, z = 0, y = -7.64, ow = 0.7908, ox = 0, oy = -0.61208, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/dressed_stormtrooper_m.iff", x = -5.38, z = 0, y = 6.54, ow = 0.20433, ox = 0, oy = 0.9789, oz = 0, cellid = -1, containmentType = -1 },
	},
}

ObjectTemplates:addTemplate(object_tangible_event_perk_wedding_garden_imperial_large_theater, "object/tangible/event_perk/wedding_garden_imperial_large_theater.iff")
