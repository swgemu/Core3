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


object_tangible_event_perk_jawas_and_droids = object_tangible_poi_base_shared_poi_base:new {
	invisible = 1,

	gameObjectType = 16410, -- Event Perk

	dataObjectComponent = "EventPerkDataComponent",
	attributeListComponent = "EventPerkAttributeListComponent",
	objectMenuComponent = "EventPerkMenuComponent",

	childObjects = {
		{ templateFile = "object/mobile/cll8_binary_load_lifter.iff", x = -3.45964, z = 0, y = -2.49066, ow = 0.91916, ox = 0, oy = 0.39389, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/eg6_power_droid.iff", x = 0.998913, z = 0, y = 2.12557, ow = 0.90581, ox = 0, oy = -0.42368, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/jawa.iff", x = 1.30946, z = 0, y = -3.11693, ow = 0.92995, ox = 0, oy = -0.36769, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/jawa.iff", x = 3.16253, z = 0, y = -0.19731, ow = 0.99099, ox = 0, oy = -0.13396, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/jawa.iff", x = 3.56061, z = 0, y = 1.83709, ow = 0.52467, ox = 0, oy = -0.85131, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/jawa.iff", x = -1.23446, z = 0, y = 1.61795, ow = 0.97997, ox = 0, oy = 0.19916, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/jawa.iff", x = -1.32319, z = 0, y = -0.458559, ow = 0.43644, ox = 0, oy = -0.89973, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/r2.iff", x = 3.03418, z = 0, y = 1.01843, ow = 0.99979, ox = 0, oy = -0.02056, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/r3.iff", x = -3.22948, z = 0, y = -0.284631, ow = 0.92318, ox = 0, oy = 0.38438, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/r4.iff", x = -0.69241, z = 0, y = 2.28217, ow = 0.801, ox = 0, oy = -0.59866, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/r5.iff", x = 0.615306, z = 0, y = -3.18913, ow = 0.74857, ox = 0, oy = -0.66306, oz = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/mobile/ra7_bug_droid.iff", x = -2.74181, z = 0, y = 0.855995, ow = 0.24787, ox = 0, oy = -0.96879, oz = 0, cellid = -1, containmentType = -1 },
	},
}

ObjectTemplates:addTemplate(object_tangible_event_perk_jawas_and_droids, "object/tangible/event_perk/jawas_and_droids.iff")
