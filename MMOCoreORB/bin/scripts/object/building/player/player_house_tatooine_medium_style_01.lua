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


object_building_player_player_house_tatooine_medium_style_01 = object_building_player_shared_player_house_tatooine_medium_style_01:new {
	lotSize = 2,
	baseMaintenanceRate = 34,
	allowedZones = {"dantooine", "lok", "tatooine"},
	childObjects = {
			{templateFile = "object/tangible/sign/player/house_address_tatooine.iff", x = -4, z = 2, y = 12.55, ox = 0, oy = -1, oz = 0, ow = 0, cellid = -1, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 6.94, z = 0.489743, y = 7.98, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1},
	},
	constructionMarker = "object/building/player/construction/construction_player_house_tatooine_medium_style_01.iff",
	length = 5,
	publicStructure = 0,
	skillMods = {
		{"private_medical_rating", 65},
		{"private_buff_mind", 100},
		{"private_med_battle_fatigue", 5}
	},
	width = 5
}

ObjectTemplates:addTemplate(object_building_player_player_house_tatooine_medium_style_01, "object/building/player/player_house_tatooine_medium_style_01.iff")
