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


object_building_player_player_guildhall_generic_style_01 = object_building_player_shared_player_guildhall_generic_style_01:new {
	lotSize = 5,
	baseMaintenanceRate = 100,
	allowedZones = {"corellia", "dantooine", "lok", "naboo", "rori", "talus", "tatooine"},
	publicStructure = 0,
	constructionMarker = "object/building/player/construction/construction_player_guildhall_corellia_style_01.iff",
	length = 7,
	width = 8,
	childObjects = {
			{templateFile = "object/tangible/sign/player/house_address.iff", x = 4.34, z = 3.4, y = 18.40, ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_player_structure.iff", x = 17.88, z= 2.75, y = 10.45, ox = 0, oy = 0.707107, oz = 0, ow = 0.707107, cellid = 7, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_elevator_up.iff", x = 0, z = -8.5, y = 13.5, ow = 0, ox = 0, oy = 1, oz = 0, cellid = 9, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_elevator_down.iff", x = 0, z = 2.75, y = 13.5, ow = 0, ox = 0, oy = 1, oz = 0, cellid = 9, containmentType = -1},
			{templateFile = "object/tangible/terminal/terminal_guild.iff", x = -17.0, z = 2.75, y = 20, ow = 0, ox = 0, oy = 1, oz = 0, cellid = 6, containmentType = -1}
	}
}

ObjectTemplates:addTemplate(object_building_player_player_guildhall_generic_style_01, "object/building/player/player_guildhall_generic_style_01.iff")
