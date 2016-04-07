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


object_tangible_event_perk_fenced_enclosure = object_tangible_poi_base_shared_poi_base:new {
	invisible = 1,

	gameObjectType = 16410, -- Event Perk

	dataObjectComponent = "EventPerkDataComponent",
	attributeListComponent = "EventPerkAttributeListComponent",
	objectMenuComponent = "EventPerkMenuComponent",

	childObjects = {
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = -8.05763, z = -0.00032, y = 0.92422, ow = 0.91712, ox = 0, oy = 0.39861, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = -0.291943, z = -0.00032, y = 7.55653, ow = 0.93765, ox = 0, oy = 0.34759, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = 0.750796, z = -0.00032, y = -11.4897, ow = 1, ox = 0, oy = 0, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = 11.9121, z = -0.00032, y = -1.25476, ow = 0.69311, ox = 0, oy = -0.72083, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = -9.4742, z = 0.00484, y = -0.33538, ow = 0.91512, ox = 0, oy = 0.40319, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_column_s02.iff", x = 1.11293, z = -0.00032, y = 8.95552, ow = 0.36701, ox = 0, oy = -0.93022, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_gate_sm_s01.iff", x = -4.22084, z = -0.00032, y = 4.09106, ow = 0.923, ox = 0, oy = -0.38481, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_wall_4x16_s03.iff", x = -4.58386, z = -0.00229, y = -5.84103, ow = 0.91512, ox = 0, oy = 0.40319, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_wall_4x16_s03.iff", x = 6.4975, z = -0.00032, y = 3.82755, ow = 0.93051, ox = 0, oy = 0.36627, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/corellia/corl_imprv_wall_4x16_s03.iff", x = 6.35514, z = -0.00032, y = -6.43399, ow = 0.93051, ox = 0, oy = -0.36627, oz = 0, cellid = -1, containmentType = -1 },
	},
}

ObjectTemplates:addTemplate(object_tangible_event_perk_fenced_enclosure, "object/tangible/event_perk/fenced_enclosure.iff")
