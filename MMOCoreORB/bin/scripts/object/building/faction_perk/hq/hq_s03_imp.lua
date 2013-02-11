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


object_building_faction_perk_hq_hq_s03_imp = object_building_faction_perk_hq_shared_hq_s03_imp:new {
		lotSize = 0,
		containerComponent = "GCWBaseContainerComponent",
		zoneComponent = "StructureZoneComponent",
		maintenanceCost = 0,
		baseMaintenanceRate = 0,
		faction = "imperial",
		pvpFaction = "imperial",
		dataObjectComponent = "DestructibleBuildingDataComponent",
		allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
		constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
		length = 7,
		width = 6,
		planetMapCategory = "imperial_hq",
		alwaysPublic = 1,
		skillMods = {
			{"private_buff_mind", 100},
			{"private_med_battle_fatigue", 5},
			{"private_medical_rating", 100},
		},
		
		childObjects = {
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-10, z=0, y=37, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=10, z=0, y=37, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},

			-- wall 2
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-14, z=0, y=32, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=14, z=0, y=32, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
		
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-18, z=0, y=29, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=18, z=0, y=29, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
		
				-- wall 4
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-22, z=0, y=25, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=22, z=0, y=25, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
		
			-- wall 5 ( 45deg)
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=18.5, z=0, y=17.5, ox=0, oy=-.395, oz=0, ow=.92, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-18.5, z=0, y=17.5, ox=0, oy=.395, oz=0, ow=.92, cellid=-1, containmentType=-1}, 
		
		
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=16, z=0, y=7,  ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=-16, z=0, y=7,  ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 

			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=12.25, z=0, y=-.75,ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-12.25, z=0, y=-.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
		
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=9, z=0, y=-6, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-9, z=0, y=-6, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
						
						
			-- back walls
			
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=0, z=0, y=-10	,   ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			
			
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-18, z=0, y=32, ox=0, oy=-0,  oz=0, ow=1, cellid=-1, containmentType=-1}, -- left turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=18, z=0, y=32,  ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-13, z=0, y=-5, ox=0, oy=.7,  oz=0, ow=-.7, cellid=-1, containmentType=-1}, -- back turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=13, z=0, y=-5,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
						
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=1.5, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=0, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=-1.5, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=-5, z=.25, y=-3, ow=.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
								
			{templateFile = "object/tangible/terminal/terminal_hq_imperial.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },
			
			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =5, z =.25, y =-4, ow =-.662, ox =0, oz = 0, oy =.749, cellid = 3, containmentType = -1},
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =-9, z =-13.75, y =4.5, ox = 0, oy =.076, oz = 0, ow =1, cellid = 7, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =-3, z =-21, y=1.5, ox=0, oy=0, oz=0, ow=1, cellid = 9, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = 4.25, z =-20.75, y =36, ox = 0, oy =1, oz = 0, ow =0, cellid = 10, containmentType = -1 },
			
			{templateFile="object/tangible/terminal/terminal_mission.iff", x=-11, z=-13.75, y=7, ow=.7, ox=0, oz=0, oy=.7, cellid=7, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_bank.iff", x=6, z=-20.75, y=13, ow=1, ox=0, oz=0, oy=0, cellid=10, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_insurance.iff", x=-2, z=-20.75, y=13, ow=1, ox=0, oz=0, oy=0, cellid=10, containmentType=-1},	
			{templateFile="object/tangible/terminal/terminal_mission_imperial.iff", x=8, z=-13.75, y=7, ow=-.7, ox=0, oz=0, oy=.7, cellid=7, containmentType=-1},

					
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=5, z=0, y=25,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=-5, z=0, y=25,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=15, z=0, y=50,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=-15, z=0, y=50,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1}, 
		
		},
		
		childCreatureObjects = {
		 	 { mobile="at_st", x=10, z=0, y=45, cellid=-1, respawn=300, containmentType=-1, heading=0},
		 	 { mobile="stormtrooper", x=15, z=0, y=45, cellid=-1, respawn=300, containmentType=-1, heading=0},
		 	 { mobile="at_st", x=-10, z=0, y=45, cellid=-1, respawn=300, containmentType=-1, heading=0},
		 	{ mobile="stormtrooper", x=-15, z=0, y=45, cellid=-1, respawn=300, containmentType=-1, heading=0},
			
			{ mobile="dark_trooper", x=3, z=0, y=27, cellid=-1, respawn=300, containmentType=-1, heading=.78},
			{ mobile="dark_trooper", x=-3, z=0, y=27, cellid=-1, respawn=300, containmentType=-1, heading=.78},
		
		
			{ mobile="dark_trooper", x=6, z=0, y=20, cellid=-1, respawn=300, containmentType=-1, heading=0},
			{ mobile="dark_trooper", x=-6, z=0, y=20, cellid=-1, respawn=300, containmentType=-1, heading=0},
		
			{ mobile="dark_trooper", x=9, z=0, y=22, cellid=-1, respawn=300, containmentType=-1, heading=0},
			{ mobile="dark_trooper", x=-9, z=0, y=22, cellid=-1, respawn=300, containmentType=-1, heading=0},
		
			 { mobile="dark_trooper", x=4, z=-3.25, y=5, cellid=4, respawn=300, containmentType=-1, heading=1.57},
		 
		 	{ mobile="dark_trooper", x=-4, z=-10.25, y=-6, cellid=5, respawn=300, containmentType=-1, heading=1.57},
		 
			 { mobile="stormtrooper", x=-2.7, z=-13.75, y=7, cellid=7, respawn=300, containmentType=-1, heading=1.57},
			 { mobile="dark_trooper", x=-5, z=-13.75, y=7, cellid=7, respawn=300, containmentType=-1, heading=1.57},
			 
			 { mobile="dark_trooper", x=4, z=-20.75, y=6, cellid=9, respawn=300, containmentType=-1, heading=4.7},
			 { mobile="dark_trooper", x=-1.5, z=-20.75, y=6, cellid=9, respawn=300, containmentType=-1, heading=1.57},
		 
			 { mobile="stormtrooper", x=4.5, z=-20.75, y=15.8, cellid=10, respawn=300, containmentType=-1, heading=4.7},
			 { mobile="dark_trooper", x=-2, z=-20.75, y=15.8, cellid=10, respawn=300, containmentType=-1, heading=1.57},
		 
			 { mobile="imperial_recruiter", x=-5, z=-20.75, y=32, cellid=10, containmentType=-1, respawn=60, heading=1.57},
		},

}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s03_imp, "object/building/faction_perk/hq/hq_s03_imp.iff")
