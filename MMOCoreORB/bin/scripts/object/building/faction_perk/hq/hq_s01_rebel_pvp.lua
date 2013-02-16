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


object_building_faction_perk_hq_hq_s01_rebel_pvp = object_building_faction_perk_hq_shared_hq_s01_rebel_pvp:new {
		lotSize = 0,
		faction = "rebel",
		pvpFaction = "rebel",
		pvpStatusBitmask = OVERT,
		maintenanceCost = 0,
		baseMaintenanceRate = 0,
		dataObjectComponent = "DestructibleBuildingDataComponent",
		zoneComponent = "StructureZoneComponent",
		allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
		constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
		length = 7,
		width = 6,
		containerComponent = {"cpp", "GCWBaseContainerComponent"},
		planetMapCategory = "rebel_hq",
			childObjects = {

		
			-- left side columns
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-5, z=0, y=14, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 1
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-13, z=0, y=14, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 2
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-13, z=0, y=5, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 3
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-7.34, z=0, y=-.66, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 4
			--{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-21, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 5
			--{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=-4.5, z=0, y=-11, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 6
		
			-- right side columns
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=5, z=0, y=14, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 1
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=13, z=0, y=14, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 2
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=13, z=0, y=5, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 3
			{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=7.34, z=0, y=-.66, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 4
		--	{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=15.34, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 5
		--	{templateFile = "object/static/structure/military/military_column_weak_rebel_style_01.iff", x=4.5, z=0, y=-11, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 6
		
		
				-- back columns
			--{templateFile = "object/static/structure/military/military_column_weak_rebl_style_01.iff", x=4, z=0, y=-11, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column
			--{templateFile = "object/static/structure/military/military_column_weak_rebl_style_01.iff", x=-4, z=0, y=-11, ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			
		
			-- wall 1
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=-9.5, z=0, y=14, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left wall 1
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=9.5, z=0, y=14, ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			
			
			-- Wall 2
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=-13, z=0, y=10, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=13, z=0, y=10, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
			-- Wall 3
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=10.2, z=0, y=2.12, ox=0, oy=-.38, oz=0, ow=.922, cellid=-1, containmentType=-1}, -- left wall 3
			{templateFile = "object/static/structure/military/military_wall_weak_rebl_style_01.iff", x=-10.2, z=0, y=2.12, ox=0, oy=.38, oz=0, ow=.9222, cellid=-1, containmentType=-1},   --right
		
			-- turret
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-17, z=0, y=9, ox=0, oy=-0,  oz=0, ow=1, cellid=-1, containmentType=-1}, -- left turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=17, z=0, y=9,  ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			
			--minefield
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=0, z=0, y=12,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-1.5, z=0, y=-1.8, ow=.7, ox=0, oz=0, oy=.7, cellid=3, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-1.5, z=0, y=-.5, ow=.7, ox=0, oz=0, oy=.7, cellid=3, containmentType=-1},
			
			{templateFile="object/tangible/terminal/terminal_mission_rebel.iff", x=-1, z=0, y=3, ow=1, ox=0, oz=0, oy=0, cellid=1, containmentType=-1},
			
		
		
			 {templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = 0, z = 0, y = -6, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 3, containmentType = -1 },
 			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x = 4, z = 0, y = -5.8, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x = 3.8, z = 0, y = -0.8, ox = 0, oy = 1, oz = 0, ow = 1, cellid = 4, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = -4, z = 0, y = -.5, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 6, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x = 1, z = 0, y = -1, ow =-.685, ox =0, oz = 0, oy =.728, cellid = 3, containmentType = -1},
			},

		childCreatureObjects = {

			{ mobile="rebel_first_lieutenant", x=3.6, z=0, y=1.8, cellid=4, respawn=300, containmentType=-1, heading=0}, 
			{ mobile="rebel_medic", x=-3.8, z=0, y=-2.3, cellid=6, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_recruiter", x=-1, z=0, y=-5.5, cellid=3, containmentType=-1, respawn=60, heading=0},
		},
		
}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s01_rebel_pvp, "object/building/faction_perk/hq/hq_s01_rebel_pvp.iff")
