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


object_building_faction_perk_hq_hq_s04_rebel_pvp = object_building_faction_perk_hq_shared_hq_s04_rebel_pvp:new {
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
		factionBaseType = 1,

		skillMods = {
			{"private_buff_mind", 100},
			{"private_med_battle_fatigue", 5},
			{"private_medical_rating", 100},
		--will need to revisit the elite skill mod bonus functionality later
		},

	--Make register with location function for Docs Mus Danc later too

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

			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=5, z=0, y=23,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1},
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=-5, z=0, y=23,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1},

			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=15, z=0, y=45,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=-15, z=0, y=45,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1},

			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=1.5, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=0, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=-1.5, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=-3, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},

			{templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },

			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =5, z =.25, y =-4, ow =-.662, ox =0, oz = 0, oy =.749, cellid = 3, containmentType = -1},
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =-5, z =-13.75, y =4.5, ox = 0, oy =.076, oz = 0, ow =1, cellid = 7, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =3, z =-20.75, y=1.5,  ox=0, oy=0, oz=0, ow=1, cellid = 9, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = 4.25, z =-20.75, y =36, ox = 0, oy =1, oz = 0, ow =0, cellid = 10, containmentType = -1 },

			{templateFile="object/tangible/terminal/terminal_mission.iff", x=-11, z=-13.75, y=7, ow=.7, ox=0, oz=0, oy=.7, cellid=7, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_bank.iff", x=6, z=-13.75, y=10, ow=0, ox=0, oz=0, oy=1, cellid=7, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_insurance.iff", x=-9, z=-13.75, y=10, ow=0, ox=0, oz=0, oy=1, cellid=7, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_mission_rebel.iff", x=8, z=-13.75, y=7, ow=-.7, ox=0, oz=0, oy=.7, cellid=7, containmentType=-1},

		},

		childCreatureObjects = {
			{ mobile="specforce_technician", x=4.25, z=0, y=1.1, cellid=2, respawn=300, containmentType=-1, heading=1.57},
		 	{ mobile="senior_specforce_technician", x=4.25, z=0, y=-1.8, cellid=2, respawn=300, containmentType=-1, heading=1.57},

		 	{ mobile="senior_specforce_lieutenant", x=-3.25, z=0, y=-3.7, cellid=3, respawn=300, containmentType=-1, heading=1.57},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=4.75, z=-6.75, y=5.2, cellid=4, respawn=300, containmentType=-1, heading=4.71},

			{ mobile="senior_specforce_marine", x=3.5, z=-6.75, y=-3, cellid=5, respawn=300, containmentType=-1, heading=0},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=5, z=-6.75, y=-3, cellid=5, respawn=300, containmentType=-1, heading=0},
			{ mobile="senior_specforce_marine", x=7, z=-6.75, y=-1, cellid=5, respawn=300, containmentType=-1, heading=1.57},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=1.75, z=-6.75, y=-1, cellid=5, respawn=300, containmentType=-1, heading=4.71},
			{ mobile="specforce_major", x=6.4, z=-6.75, y=-8.25, cellid=5, respawn=300, containmentType=-1, heading=0},

			{ mobile="senior_specforce_marine", x=-0.1, z=-13.75, y=5.6, cellid=7, respawn=300, containmentType=-1, heading=3.14},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=-3.5, z=-13.75, y=4.6, cellid=7, respawn=300, containmentType=-1, heading=3.14},
			{ mobile="senior_specforce_technician", x=-2.3, z=-13.75, y=-3.5, cellid=7, respawn=300, containmentType=-1, heading=1.57},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=-0.35, z=-13.75, y=-13.35, cellid=7, respawn=300, containmentType=-1, heading=4.71},
			{ mobile="specforce_major", x=-1, z=-13.75, y=0.35, cellid=7, respawn=300, containmentType=-1, heading=4.71},

			{ mobile="rebel_medic", x=5.25, z=-13.75, y=9.9, cellid=8, respawn=300, containmentType=-1, heading=0},
			{ mobile="rebel_specforce_colonel", x=-5.25, z=-13.75, y=14.25, cellid=8, respawn=300, containmentType=-1, heading=3.14},

			{ mobile="senior_specforce_marine", x=17.9, z=-13.75, y=-0.8, cellid=9, respawn=300, containmentType=-1, heading=0},
			{ mobile="senior_specforce_marine", x=12.7, z=-13.75, y=-0.8, cellid=9, respawn=300, containmentType=-1, heading=0},

			{ mobile="rebel_general", x=16.1, z=-13.75, y=-16.8, cellid=10, respawn=300, containmentType=-1, heading=0},
			{ mobile="senior_specforce_heavy_weapons_specialist", x=14.2, z=-13.75, y=-10, cellid=10, respawn=300, containmentType=-1, heading=0},
			{ mobile="senior_specforce_marine", x=15, z=-13.75, y=-4, cellid=10, respawn=300, containmentType=-1, heading=0},

			 { mobile="rebel_recruiter", x=11.5, z=-11.5, y=-21, cellid=10, containmentType=-1, respawn=60, heading=1.59},
		},

}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s04_rebel_pvp, "object/building/faction_perk/hq/hq_s04_rebel_pvp.iff")