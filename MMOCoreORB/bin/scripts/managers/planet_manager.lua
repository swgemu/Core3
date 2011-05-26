--Copyright (C) 2007 <SWGEmu>
 
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
--which carries forward this exception.

corellia = {
	planetTravelPoints = {
		{name = "Coronet Shuttle B", x = -329.76605, z = 28, y = -4641.23, interplanetaryTravelAllowed = 0},
		{name = "Coronet Shuttle A", x = -25.671804, z = 28, y = -4409.7847, interplanetaryTravelAllowed = 0},
		{name = "Coronet Starport", x = -66.760902, z = 28, y = -4711.3281, interplanetaryTravelAllowed = 1},
		{name = "Vreni Island Shuttle", x = -5551.9473, z = 15.890146, y = -6059.9673, interplanetaryTravelAllowed = 1},
		{name = "Tyrena Shuttle B", x = -5600.6367, z = 21, y = -2790.7429, interplanetaryTravelAllowed = 0},
		{name = "Tyrena Shuttle A", x = -5005.354, z = 21, y = -2386.9819, interplanetaryTravelAllowed = 0},
		{name = "Tyrena Starport", x = -5003.0649, z = 21, y = -2228.3665, interplanetaryTravelAllowed = 1},
		{name = "Kor Vella Shuttleport", x = -3775.2546, z = 86, y = 3234.2202, interplanetaryTravelAllowed = 0},
		{name = "Kor Vella Starport", x = -3157.2834, z = 86, y = 2876.2029, interplanetaryTravelAllowed = 1},
		{name = "Doaba Guerfel Shuttleport", x = 3085.4963, z = 280, y = 4993.0098, interplanetaryTravelAllowed = 0},
		{name = "Doaba Guerfel Starport", x = 3349.8933, z = 308, y = 5598.1362, interplanetaryTravelAllowed = 1},
		{name = "Bela Vistal Shuttleport A", x = 6644.269, z = 330, y = -5922.5225, interplanetaryTravelAllowed = 0},
		{name = "Bela Vistal Shuttleport B", x = 6930.8042, z = 330, y = -5534.8936, interplanetaryTravelAllowed = 0}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.664289, oz = 0, ow = 0.747476, x = -133.192, z = 28, y = -4711.16, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.346712, oz = 0, ow = 0.937972, x = -5049.64, z = 21, y = -2304.52, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.290803, oz = 0, ow = 0.956783, x = 3330.38, z = 308, y = 5517.14, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.666281, oz = 0, ow = 0.745701, x = -136.437, z = 28, y = -4730.23, parentid = 0}
	}
}

dantooine = {
	planetTravelPoints = {
		{name = "Dantooine Mining Outpost", x = -635.96887, z = 3, y = 2507.0115, interplanetaryTravelAllowed = 1},
		{name = "Dantooine Imperial Outpost", x = -4208.6602, z = 3, y = -2350.24, interplanetaryTravelAllowed = 1},
		{name = "Dantooine Agro Outpost", x = 1569.66, z = 4, y = -6415.7598, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.695864, oz = 0, ow = 0.718174, x = 1585.68, z = 4, y = -6368.95, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.725999, oz = 0, ow = -0.687696, x = -629.417, z = 3, y = 2481.24, parentid = 0}
 	}
}

dathomir = {
	planetTravelPoints = {
		{name = "Dathomir Outpost", x = 618.89258, z = 6.039608, y = 3092.0142, interplanetaryTravel = 1},
		{name = "Science Outpost", x = -49.021923, z = 18, y = -1584.7278, interplanetaryTravel = 1} 
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.701463, oz = 0, ow = 0.712705, x = 592.612, z = 6, y = 3089.84, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.314904, oz = 0, ow = 0.949123, x = -67.6585, z = 18, y = -1595.3, parentid = 0}
	}
}

endor = {
	planetTravelPoints = {
		{name = "Smuggler Outpost", x = -950.59241, z = 73, y = 1553.4125, interplanetaryTravelAllowed = 1},
		{name = "Research Outpost", x = 3201.6599, z = 24, y = -3499.76, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.932952, oz = 0, ow = -0.360002, x = -963.537, z = 73, y = 1556.86, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.723459, oz = 0, ow = -0.690367, x = 3240.5, z = 24, y = -3484.79, parentid = 0}
	}
}

lok = {
	planetTravelPoints = {
		{name = "Nym's Stronghold", x = 478.92676, z = 9, y = 5511.9565, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.999879, oz = 0, ow = 0.015506, x = 464.677, z = 8.75806, y = 5506.49, parentid = 0}
	}
}

naboo = {
	planetTravelPoints = {
		{name = "Keren Starport", x = 1371.5938, z = 13, y = 2747.9043, interplanetaryTravelAllowed = 1},
		{name = "Keren Shuttleport South", x = 1567.5193, z = 25, y = 2837.8777, interplanetaryTravelAllowed = 0},
		{name = "Keren Shuttleport", x = 2021.0026, z = 19, y = 2525.679, interplanetaryTravelAllowed = 0},
		{name = "Theed Shuttle B", x = -5856.1055, z = 6, y = 4172.1606, interplanetaryTravelAllowed = 0},
		{name = "Theed Shuttle C", x = -5411.0171, z = 6, y = 4322.3315, interplanetaryTravelAllowed = 0},
		{name = "Theed Spaceport", x = -4858.834, z = 5.9483199, y = 4164.0679, interplanetaryTravelAllowed = 1},
		{name = "The Lake Retreat", x = -5494.4224, z = -150, y = -21.837162, interplanetaryTravelAllowed = 0},
		{name = "Moenia", x = 4731.1743, z = 4.1700001, y = -4677.5439, interplanetaryTravelAllowed = 1},
		{name = "Moenia Shuttleport", x = 4961.9409, z = 3.75, y = -4892.6997, interplanetaryTravelAllowed = 0},
		{name = "Dee'ja Peak Shuttleport", x = 5331.9375, z = 327.02765, y = -1576.6733, interplanetaryTravelAllowed = 0},
		{name = "Kaadara Starport", x = 5280.2002, z = -192, y = 6688.0498, interplanetaryTravelAllowed = 1},
		{name = "Kaadara Shuttleport", x = 5123.3857, z = -192, y = 6616.0264, interplanetaryTravelAllowed = 0}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.715602, oz = 0, ow = -0.698509, x = 4824.53, z = 4.17, y = -4704.9, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.309582, oz = 0, ow = 0.950873, x = -4876.99, z = 6, y = 4142.12, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0116238, oz = 0, ow = 0.999932, x = 5193.14, z = -192, y = 6680.25, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0116238, oz = 0, ow = -0.686427, x = 1445.8, z = 13, y = 2771.98, parentid = 0}
	}
}

rori = {
	planetTravelPoints = {
		{name = "Restuss Starport", x = 5301.498, z = 80, y = 6189.1694, interplanetaryTravelAllowed = 1},
		{name = "Restuss Shuttleport", x = 5220.1011, z = 79.9114, y = 6204.8433, interplanetaryTravelAllowed = 0},
		{name = "Narmle Starport", x = -5374.0718, z = 80, y = -2188.6143, interplanetaryTravelAllowed = 1},
		{name = "Narmle Shuttleport", x = -5255.4116, z = 80.664185, y = -2161.6274, interplanetaryTravelAllowed = 0},
		{name = "Rebel Outpost", x = 3691.9023, z = 96, y = -6403.4404, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.100263, oz = 0, ow = 0.994961, x = -5307.37, z = 80.1274, y = -2216.91, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.69192, oz = 0, ow = 0.721974, x = 5370.22, z = 80, y = 5666.04, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0274543, oz = 0, ow = 0.999623, x = 3672.91, z = 96, y = -6441.07, parentid = 0}
	}
}

talus = {
	planetTravelPoints = {
		{name = "Dearic Starport", x = 263.58401, z = 6, y = -2952.1284, interplanetaryTravelAllowed = 1},
		{name = "Dearic Shuttleport", x = 699.297, z = 6, y = -3041.4199, interplanetaryTravelAllowed = 1},
		{name = "Talus Imperial Outpost", x = -2229.5225, z = 20, y = 2321.854, interplanetaryTravelAllowed = 1},
		{name = "Nashal Shuttleport", x = 4334.5786, z = 9.8999996, y = 5431.0415, interplanetaryTravelAllowed = 1},
		{name = "Nashal Starport", x = 4453.7212, z = 2, y = 5354.3345, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.996369, oz = 0, ow = -0.0851417, x = 4447.08, z = 2, y = 5286.96, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.692641, oz = 0, ow = 0.721282, x = 329.666, z = 6, y = -2924.69, parentid = 0}
	}
}

tatooine = {
	planetTravelPoints = {
		{name = "Mos Eisley Shuttleport", x = 3416.6914, z = 5, y = -4648.1411, interplanetaryTravelAllowed = 0},
		{name = "Mos Eisley Starport", x = 3599.894, z = 5, y = -4780.4487, interplanetaryTravelAllowed = 1},
		{name = "Bestine Starport", x = -1361.1917, z = 12, y = -3600.0254, interplanetaryTravelAllowed = 1},
		{name = "Bestine Shuttleport", x = -1098.4836, z = 12, y = -3563.5342, interplanetaryTravelAllowed = 0},
		{name = "Mos Espa Shuttleport South", x = -2897.0933, z = 5, y = 1933.4144, interplanetaryTravelAllowed = 0},
		{name = "Mos Espa Shuttleport West", x = -3112.1296, z = 5, y = 2176.9607, interplanetaryTravelAllowed = 0},
		{name = "Mos Espa Starport", x = -2833.1609, z = 5, y = 2107.3787, interplanetaryTravelAllowed = 1},
		{name = "Mos Espa Shuttleport East", x = -2803.511, z = 5, y = 2182.9648, interplanetaryTravelAllowed = 0},
		{name = "Anchorhead Shuttleport", x = 47.565128, z = 52, y = -5338.9072, interplanetaryTravelAllowed = 0},
		{name = "Mos Entha Spaceport", x = 1266.0996, z = 7, y = 3065.1392, interplanetaryTravelAllowed = 1},
		{name = "Mos Entha Shuttle B", x = 1395.447, z = 7, y = 3467.0117, interplanetaryTravelAllowed = 0},
		{name = "Mos Entha Shuttle A", x = 1730.8828, z = 7, y = 3184.6135, interplanetaryTravelAllowed = 0}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.768226, oz = 0, ow = -0.640178, x = 3533.04, z = 5, y = -4796, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.486657, oz = 0, ow = 0.873593, x = -1271.07, z = 12, y = -3590.22, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.514176, oz = 0, ow = 0.857684, x = -2896.35, z = 5, y = 2130.87, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.989124, oz = 0, ow = -0.147086, x = 1299.08, z = 7, y = 3145.21, parentid = 0}
	}
}

yavin4 = {
	planetTravelPoints = {
		{name = "Yavin IV Labor Outpost", x = -6921.6733, z = 73, y = -5726.5161, interplanetaryTravelAllowed = 1},
		{name = "Yavin IV Mining Outpost", x = -267.23914, z = 35, y = 4896.3013, interplanetaryTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.705623, oz = 0, ow = 0.708587, x = -6917.18, z = 73, y = -5732.25, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.723339, oz = 0, ow = -0.690493, x = 4057.69, z = 37, y = -6217.54, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.00721678, oz = 0, ow = 0.999974, x = -293.367, z = 35, y = 4854.52, parentid = 0}
	}
}

space_corellia = {
}

tutorial = {
}

dungeon1 = {
}