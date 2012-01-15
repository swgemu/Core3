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


object_building_poi_scout_camp_s4 = object_building_poi_shared_scout_camp_s4:new {
templateType = CAMPSTRUCTURE,
	lotSize = 0,
	baseMaintenanceRate = 0,
	basePowerRate = 0,

	medicalRating = 90,	

	healthWoundRegenRate = 80,
	actionWoundRegenRate = 80,
	mindWoundRegenRate = 0,
	
	aggroMod = 75,
	duration = 3600,
	radius = 20,
	experience = 0,
	skillRequired = 95,

	childObjects = {
		{templateFile = "object/tangible/camp/camp_control_panel.iff", 
			x = -4.5, z = 0, y = 12.3, 
			ox = 0, oy = .95, oz = 0, ow = 0.1, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/campfire_logs_fresh.iff", 
			x = 1, z = 0, y = 0, 
			ox = 0, oy = 0, oz = 0, ow = 0, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/static/particle/particle_campfire_style_1.iff", 
			x = 1, z = 0, y = 0, 
			ox = 0, oy = 0, oz = 0, ow = 0, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/crafting/station/public_food_station.iff", 
			x = 10.5, z = 0, y = -2, 
			ox = 0, oy = .72, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/crafting/station/public_weapon_station.iff", 
			x = 4.5, z = 0, y = 13.5, 
			ox = 0, oy = .72, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -3.1, z = 0, y = 1.7, 
			ox = 0, oy = 0, oz = .0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -4.7, z = 0, y = 3.6, 
			ox = 0, oy = .7, oz = 0, ow = .75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -2.5, z = 0, y = -.3, 
			ox = 0, oy = .7, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -4.1, z = 0, y = -1.7, 
			ox = 0, oy = 0, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -5.7, z = 0, y = -0.2, 
			ox = 0, oy = -.7, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -7.7, z = 0, y = 1.7, 
			ox = 0, oy = 0, oz = 0, ow = -.75, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/camp/camp_chair_s3.iff", 
			x = -7.7, z = 0, y = 4.0, 
			ox = 0, oy = 1, oz = 0, ow = 0, 
			cellid = -1, 
			containmentType = -1},

		{templateFile = "object/tangible/furniture/all/frn_all_gaming_kiosk_s01.iff", 
			x = -7.7, z = 0, y = 4.0, 
			ox = 0, oy = 1, oz = 0, ow = 0, 
			cellid = -1, 
			containmentType = -1},
	}
}

ObjectTemplates:addTemplate(object_building_poi_scout_camp_s4, "object/building/poi/scout_camp_s4.iff")
