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


object_building_tatooine_cloning_facility_tatooine = object_building_tatooine_shared_cloning_facility_tatooine:new {
	gameObjectType = 519,
	planetMapCategory = "cloningfacility",


	childObjects = {
		{templateFile = "object/tangible/terminal/terminal_cloning.iff", x = 1, z = -0.05, y = 2.5, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1},
		{templateFile = "object/tangible/terminal/terminal_cloning.iff", x = 1, z = -0.05, y = -1.35, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1}
	},
	spawningPoints = { 			
			{ x = -16.6514, z = -4.29167, y = -10.4976, ow = 0.704753, ox = 0, oz = 0, oy = 0.709453, cellid = 5 }, 
			{ x = -16.5965, z = -4.29167, y = -14.1652, ow = 0.692575, ox = 0, oz = 0, oy = 0.721346, cellid = 5 }, 
			{ x = 16.5771, z = -4.29167, y = -14.2091, ow = -0.702231, ox = 0, oz = 0, oy = 0.71195, cellid = 5 }, 
			{ x = 16.6876, z = -4.29167, y = -10.5391, ow = 0.716877, ox = 0, oz = 0, oy = -0.6972, cellid = 5 }, 
			{ x = 6.32992, z = -4.79167, y = 0.613332, ow = 0.00405023, ox = 0, oz = 0, oy = 0.999992, cellid = 5 }, 
			{ x = 1.58067, z = -4.79167, y = 1.00877, ow = -0.143217, ox = 0, oz = 0, oy = 0.989691, cellid = 5 }, 
			{ x = -2.84125, z = -4.79167, y = 1.26153, ow = 0.999366, ox = 0, oz = 0, oy = -0.0356012, cellid = 5 }
			}, -- { x, z, y, ow, ox, oy, oz, cellid }
	templateType = CLONINGBUILDING
}

ObjectTemplates:addTemplate(object_building_tatooine_cloning_facility_tatooine, "object/building/tatooine/cloning_facility_tatooine.iff")
