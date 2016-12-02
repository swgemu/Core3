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


object_building_poi_scout_camp_s3 = object_building_poi_shared_scout_camp_s3:new {
	-- High Quality Camp
	templateType = CAMPSTRUCTURE,
	lotSize = 0,
	baseMaintenanceRate = 0,
	basePowerRate = 0,

	skillMods = {
		{"private_safe_logout", 1},
		{"private_medical_rating", 80},
		{"private_med_wound_health", 60},
		{"private_med_wound_action", 60},
		{"private_aggro_mod", 50},
		{"private_buff_mind", 100}
	},

	aggroMod = 50,

	duration = 3600,
	radius = 20,
	experience = 1000,
	skillRequired = 50,

	childObjects = {
		{templateFile = "object/tangible/camp/camp_control_panel.iff", x = -2.58, z = 0, y = -1.96, ox = 0, oy = 0.585, oz = 0, ow = 0.811, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s1.iff", x = 7.19, z = 0, y = -3.23, ox = 0, oy = 0.435, oz = 0, ow = 0.900, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s1.iff", x = 7.29, z = 0, y = -4.25, ox = 0, oy = 0.849, oz = 0, ow = 0.528, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s2.iff", x = .52, z = 0, y = -1.9, ox = 0, oy = -0.015, oz = 0, ow = 1.000, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s2.iff", x = .79, z = 0, y = 2.2, ox = 0, oy = -0.996, oz = 0, ow = 0.084, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s2.iff", x = -.81, z = 0, y = 1.9, ox = 0, oy = 0.959, oz = 0, ow = 0.282, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s2.iff", x = 1.88, z = 0, y = -1.1, ox = 0, oy = -0.484, oz = 0, ow = 0.875, cellid = -1, containmentType = -1},
		{templateFile = "object/tangible/camp/camp_chair_s2.iff", x = 2.07, z = 0, y = 1.43, ox = 0, oy = -0.919, oz = 0, ow = 0.393,	cellid = -1, containmentType = -1},
	}
}

ObjectTemplates:addTemplate(object_building_poi_scout_camp_s3, "object/building/poi/scout_camp_s3.iff")
