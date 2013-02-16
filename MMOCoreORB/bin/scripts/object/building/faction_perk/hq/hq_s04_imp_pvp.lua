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


object_building_faction_perk_hq_hq_s04_imp_pvp = object_building_faction_perk_hq_shared_hq_s04_imp_pvp:new {
		lotSize = 0,
		containerComponent = "GCWBaseContainerComponent",
		zoneComponent = "StructureZoneComponent",
		maintenanceCost = 0,
		baseMaintenanceRate = 0,
		faction = "imperial",
		pvpFaction = "imperial",
		pvpStatusBitmask = OVERT,
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

			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=7, z=0, y=27.5, ox=0, oy=.4, oz=0, ow=.9, cellid=-1, containmentType=-1}, -- Front right
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-7, z=0, y=27.5, ox=0, oy=-.4, oz=0, ow=.9, cellid=-1, containmentType=-1},
				
			-- wall 2
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-10, z=0, y=20.5, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=10, z=0, y=20.5, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
						
			-- wall 3
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-14, z=0, y=16.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left wall 3
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=14, z=0, y=16.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right wall 3
						
			-- wall 4
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=-18, z=0, y=8.75, ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 4
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=18, z=0, y=8.75, ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
			-- wall 5
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=15, z=0, y=-2, oy=-.4, oz=0, ow=.9, cellid=-1, containmentType=-1},-- right wall 5	
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-15, z=0, y=-2, ox=0, oy=.4, oz=0, ow=.9, cellid=-1, containmentType=-1}, -- left wall 5
			
			-- wall 6
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=15, z=0, y=-8.5, ox=0, oy=.4, oz=0, ow=.9, cellid=-1, containmentType=-1}, -- right wall 6
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-15, z=0, y=-8.5, ox=0, oy=-.4, oz=0, ow=.9, cellid=-1, containmentType=-1}, -- left wall 6
			
			
			-- wall 7 changed form 16 to 15 in y
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=15, z=0, y=-14.5, oy=-.4, oz=0, ow=.9, cellid=-1, containmentType=-1},-- right wall 7	
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-15, z=0, y=-14.5, ox=0, oy=.4, oz=0, ow=.9, cellid=-1, containmentType=-1}, -- left wall 7
			
			-- back walls
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-8, z=0, y=-17, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-0, z=0, y=-17, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=8, z=0, y=-17, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			
			-- turret
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-15, z=0, y=20, ox=0, oy=-0,  oz=0, ow=1, cellid=-1, containmentType=-1}, -- left turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=15, z=0, y=20,  ox=0, oy=0, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=-17, z=0, y=-5.5, ox=0, oy=.7,  oz=0, ow=-.7, cellid=-1, containmentType=-1}, -- back turret front
			{templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x=17, z=0, y=-5.5,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
						
			{templateFile = "object/tangible/terminal/terminal_hq_imperial.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = 14, z=-13.8, y=-4, ox = 0, oy =1, oz = 0, ow =0, cellid = 10, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x = 12.75, z = -13.75, y = 10.2, ox = 0, oy = .7, oz = 0, ow =.7, cellid = 9, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x = -5.5, z = -13.75, y = 7.5, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 7, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x = 6.5, z = -6.75, y = -10, ow =1, ox =0, oz = 0, oy =0, cellid = 5, containmentType = -1},
			
			
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=5, z=.25, y=2, ow=-.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=5, z=.25, y=.5, ow=-.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=5, z=.25, y=-1, ow=-.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			{templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x=5, z=.25, y=-2.5, ow=-.7, ox=0, oz=0, oy=.7, cellid=2, containmentType=-1},
			
					
			{templateFile="object/tangible/terminal/terminal_mission.iff", x=18.25, z=-13.75, y=12.75, ow=-.69, ox=0, oz=0, oy=.71, cellid=9, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_bank.iff", x=-7, z=-13.75, y=-3.3, ow=.7, ox=0, oz=0, oy=.66, cellid=7, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_insurance.iff", x=-8, z=-13.75, y=11.75, ow=.7, ox=0, oz=0, oy=.7, cellid=8, containmentType=-1},
			{templateFile="object/tangible/terminal/terminal_mission_imperial.iff", x=-3, z=.25, y=-5.5, ow=1, ox=0, oz=0, oy=0, cellid=3, containmentType=-1},
					
			
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=7, z=0, y=45,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=-7, z=0, y=45,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x=0, z=0, y=25,  ox=0, oy=.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=15, z=0, y=35,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1}, 
			{templateFile = "object/installation/faction_perk/covert_detector/detector_base.iff", x=-15, z=0, y=35,  ox=0, oy=-.3, oz=0, ow=1, cellid=-1, containmentType=-1}, 
	

		},
		
		childCreatureObjects = {

			 { mobile="stormtrooper", x=3.5, z=-6.75, y=-3, cellid=5, respawn=300, containmentType=-1, heading=0},
			 { mobile="dark_trooper", x=5, z=-6.75, y=-3, cellid=5, respawn=300, containmentType=-1, heading=0},
			 { mobile="stormtrooper", x=14.2, z=-13.75, y=-10, cellid=10, respawn=300, containmentType=-1, heading=0},
			 { mobile="dark_trooper", x=15, z=-13.75, y=-4,cellid=10, respawn=300, containmentType=-1, heading=0},
			 { mobile="imperial_recruiter", x=11.5, z=-11.5, y=-21, cellid=10, containmentType=-1, 
			  	respawn=60, heading=1.59},
		},

}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s04_imp_pvp, "object/building/faction_perk/hq/hq_s04_imp_pvp.iff")
