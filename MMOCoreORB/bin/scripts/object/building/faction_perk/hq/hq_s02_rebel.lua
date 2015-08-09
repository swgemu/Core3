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


object_building_faction_perk_hq_hq_s02_rebel = object_building_faction_perk_hq_shared_hq_s02_rebel:new {
		lotSize = 0,
		faction = "rebel",
		pvpFaction = "rebel",
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
		factionBaseType = 1,

		skillMods = {
			{"private_medical_rating", 100},
			{"private_med_wound_health", 100},
			{"private_med_wound_action", 100},
		},

		childObjects = {

			-- left side columns
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=-5.5, z=0, y=30.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 1
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=-12.5, z=0, y=26.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 2
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=-19.5, z=0, y=22.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 3
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=-11.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 5
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=-3.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 6

			-- right columns
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=5.5, z=0, y=30.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 1
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=12.5, z=0, y=26.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 2
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=19.5, z=0, y=22.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 3
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=11.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 5
			{templateFile = "object/static/structure/military/military_column_med_rebel_style_01.iff", x=3.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 6

			-- new walls top
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-5.5, z=0, y=34.75, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=5.5, z=0, y=34.75, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1},

			-- walls 2
			{templateFile = "object/static/structure/military/military_wall_med_rebl_16_style_01.iff", x=-12.5, z=0, y=26.75, oy=-.27, oz=0, ow=.965, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_med_rebl_16_style_01.iff", x=12.5, z=0, y=26.75, oy=.27, oz=0, ow=.965, cellid=-1, containmentType=-1},

			-- middle wall 3
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-19.5, z=0, y=18.25, ox=0, oy=.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- left wall 3
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=19.5, z=0, y=18.25, ox=0, oy=-.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- right wall 3
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-19.5, z=0, y=12.25, ox=0, oy=.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- left wall 3a
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=19.5, z=0, y=12.25, ox=0, oy=-.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- right wall 3a
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-19.5, z=0, y=4.75, ox=0, oy=.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- left wall 3b
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=19.5, z=0, y=4.75, ox=0, oy=-.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- right wall 3b

			--slanted back walls
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=16.5, z=0, y=-1, oy=-.27, oz=0, ow=.965, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-16.5, z=0, y=-1, oy=.27, oz=0, ow=.965, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-12.5, z=0, y=-5, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 2b straight
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=12.5, z=0, y=-5, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1},

			-- back walls
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=-8.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=8.5, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_rebl_style_01.iff", x=0, z=0, y=-10, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},

			-- turrets
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-14.5, z=0, y=30.5, ox=0, oy=0,  oz=0, ow=1, cellid=-1, containmentType=-1}, -- left turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=14.5, z=0, y=30.5,  ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-17, z=0, y=-5.5, ox=0, oy=1,  oz=0, ow=-.27, cellid=-1, containmentType=-1}, -- back turret left
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=17, z=0, y=-5.5,  ox=0, oy=1, oz=0, ow=.27, cellid=-1, containmentType=-1},

			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=0, z=0, y=20,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1},

			{templateFile="object/tangible/terminal/terminal_mission_rebel.iff", x=5, z=.25, y=-3, ow=-.7, ox=0, oz=0, oy=.7, cellid=3, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_mission.iff", x=5, z=.25, y=-4.75, ow=-.7, ox=0, oz=0, oy=.7, cellid=3, containmentType=-1},

			{templateFile="object/tangible/terminal/terminal_bank.iff", x=-9, z=-6.66, y=-7, ow=.7, ox=0, oz=0, oy=.7, cellid=5, containmentType=-1},

			{templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =.375, z = -6.75, y =-8, ow = 1, ox =0, oz = 0, oy = .7, cellid = 5, containmentType = -1},
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =8, z =-6.75, y =-17.75, ox = 0, oy = 0, oz = 0, ow =1, cellid = 6, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =2.75, z =-6.75, y=.25, ox = 0, oy=1, oz =0, ow =0, cellid = 7, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x =-6.5, z =-13.75, y =-17, ox = 0, oy =0, oz = 0, ow =1, cellid =9, containmentType = -1 },

		},

		childCreatureObjects = {

			{ mobile="rebel_specforce_pathfinder", x=5, z=0, y=18, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=-5, z=0, y=18, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=0, z=0, y=53, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=2.5, z=0, y=50, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=-2.5, z=0, y=50, cellid=-1, respawn=360, containmentType=-1, heading=0},

			{ mobile="specforce_marine", x=-28, z=0, y=0, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=-33, z=0, y=0, cellid=-1, respawn=360, containmentType=-1, heading=0},
		 	{ mobile="rebel_trooper", x=-30.5, z=0, y=2.5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_commando", x=-28, z=0, y=5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=-33, z=0, y=5, cellid=-1, respawn=360, containmentType=-1, heading=0},

			{ mobile="specforce_marine", x=28, z=0, y=0, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=33, z=0, y=0, cellid=-1, respawn=360, containmentType=-1, heading=0},
		 	{ mobile="rebel_trooper", x=30.5, z=0, y=2.5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_commando", x=28, z=0, y=5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=33, z=0, y=5, cellid=-1, respawn=360, containmentType=-1, heading=0},

			{ mobile="specforce_marine", x=-22, z=0, y=32, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=-27, z=0, y=32, cellid=-1, respawn=360, containmentType=-1, heading=0},
		 	{ mobile="rebel_trooper", x=-24.5, z=0, y=34.5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_commando", x=-22, z=0, y=37, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=-27, z=0, y=37, cellid=-1, respawn=360, containmentType=-1, heading=0},

			{ mobile="specforce_marine", x=22, z=0, y=32, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=27, z=0, y=32, cellid=-1, respawn=360, containmentType=-1, heading=0},
		 	{ mobile="rebel_trooper", x=24.5, z=0, y=34.5, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_commando", x=22, z=0, y=37, cellid=-1, respawn=360, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=27, z=0, y=37, cellid=-1, respawn=360, containmentType=-1, heading=0},

			{ mobile="rebel_specforce_pathfinder", x=-3.5, z=0, y=-3.9, cellid=2, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_sergeant", x=2.9, z=0, y=-4.1, cellid=3, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=-1, z=-6.75, y=-6.5, cellid=5, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=-4.5, z=-6.75, y=-3.4, cellid=5, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=-2.3, z=-6.75, y=-16.5, cellid=6, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=7.2, z=-6.75, y=-14.5, cellid=6, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=2.5, z=-6.75, y=-16.5, cellid=6, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=8, z=-6.75, y=-6, cellid=7, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_first_lieutenant", x=3, z=-6.75, y=-1.8, cellid=7, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_marine", x=-5.5, z=-13.75, y=-3, cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="specforce_heavy_weapons_specialist", x=.5, z=-13.75, y=-3 ,cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=.5, z=-13.75, y=-7.2, cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_medic", x=-5.5, z=-13.75, y=-7.2 ,cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_army_captain", x=-4.1, z=-13.75, y=-17.3 ,cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_recruiter", x=0, z=-13.75, y=-17, cellid=9, containmentType=-1, respawn=60, heading=0},

		},

}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s02_rebel, "object/building/faction_perk/hq/hq_s02_rebel.iff")