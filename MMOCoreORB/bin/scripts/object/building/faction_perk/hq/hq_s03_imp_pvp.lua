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


object_building_faction_perk_hq_hq_s03_imp_pvp = object_building_faction_perk_hq_shared_hq_s03:new {
		lotSize = 0,
		maintenanceCost = 5,
		baseMaintenanceRate = 5,
		faction = "imperial",
		pvpFaction = "imperial",
		dataObjectComponent = "DestructibleBuildingDataComponent",
		allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
		constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
		length = 7,
		width = 6,
			childObjects = {
					
					
			-- left side columns
			
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-5.5, z=0, y=30.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 1
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-12.5, z=0, y=26.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 2
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-19.5, z=0, y=22.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 3
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-19.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 4
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-11.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 5
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=-3.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- left column 6

			-- right columns
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=5.5, z=0, y=30.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 1
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=12.5, z=0, y=26.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 2
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=19.5, z=0, y=22.75, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 3
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=19.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 4
		    {templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=11.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 5
			{templateFile = "object/static/structure/military/military_column_med_imperial_style_01.iff", x=3.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1}, -- right column 6

			
			-- wall1
			
			--{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=-5.5, z=0, y=34.75, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, -- left wall 2
			--{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=5.5, z=0, y=34.75, ox=0, oy=-.7, oz=0, ow=.7, cellid=-1, containmentType=-1}, 
			
			
			-- wall 2
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=-12.5, z=0, y=26.75, oy=-.27, oz=0, ow=.965, cellid=-1, containmentType=-1}, -- left wall 2
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=12.5, z=0, y=26.75, oy=.27, oz=0, ow=.965, cellid=-1, containmentType=-1}, 
			
			-- wall 3
			{templateFile = "object/static/structure/military/military_wall_med_imperial_32_style_01.iff", x=-19.5, z=0, y=6.75, ox=0, oy=.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- left wall 3
			{templateFile = "object/static/structure/military/military_wall_med_imperial_32_style_01.iff", x=19.5, z=0, y=6.75, ox=0, oy=-.711424, oz=0, ow=-.702763, cellid=-1, containmentType=-1}, -- right wall 3
			
			-- back walls
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=-11.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_16_style_01.iff", x=11.5, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
			{templateFile = "object/static/structure/military/military_wall_med_imperial_style_01.iff", x=0, z=0, y=-9.25, ox=0, oy=-0, oz=0, ow=1, cellid=-1, containmentType=-1},
					
			
			{templateFile = "object/tangible/terminal/terminal_hq_imperial.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },
			
			{templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =5, z =.25, y =-4, ow =-.662, ox =0, oz = 0, oy =.749, cellid = 3, containmentType = -1},
			{templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =-9, z =-13.75, y =4.5, ox = 0, oy =.076, oz = 0, ow =1, cellid = 7, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =-3.5, z =-21, y =6.7, ox = 0, oy =1, oz = 0, ow =0, cellid = 9, containmentType = -1 },
			{templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = 4.25, z =-20.75, y =36, ox = 0, oy =1, oz = 0, ow =0, cellid = 10, containmentType = -1 },
			
			
		},


}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s03_imp_pvp, "object/building/faction_perk/hq/hq_s03_imp_pvp.iff")
