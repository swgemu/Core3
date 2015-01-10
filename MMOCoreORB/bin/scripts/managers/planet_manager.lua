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

--Time, in seconds, that a shuttle is away for
shuttleportAwayTime = 300
starportAwayTime = 60

--Time, in seconds, that a shuttle takes to land
shuttleportLandingTime = 11
starportLandingTime = 14

--Time, in seconds, that a shuttle is landed for
shuttleportLandedTime = 120
starportLandedTime = 120


corellia = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Coronet Shuttle B", x = -329.76605, z = 28, y = -4641.23, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Coronet Shuttle A", x = -25.671804, z = 28, y = -4409.7847, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Coronet Starport", x = -66.760902, z = 28, y = -4711.3281, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Vreni Island Shuttle", x = -5551.9473, z = 15.890146, y = -6059.9673, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Tyrena Shuttle B", x = -5600.6367, z = 21, y = -2790.7429, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Tyrena Shuttle A", x = -5005.354, z = 21, y = -2386.9819, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Tyrena Starport", x = -5003.0649, z = 21, y = -2228.3665, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Kor Vella Shuttleport", x = -3775.2546, z = 31, y = 3234.2202, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Kor Vella Starport", x = -3157.2834, z = 31, y = 2876.2029, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Doaba Guerfel Shuttleport", x = 3085.4963, z = 280, y = 4993.0098, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Doaba Guerfel Starport", x = 3349.8933, z = 308, y = 5598.1362, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Bela Vistal Shuttleport A", x = 6644.269, z = 330, y = -5922.5225, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Bela Vistal Shuttleport B", x = 6930.8042, z = 330, y = -5534.8936, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.664289, oz = 0, ow = 0.747476, x = -133.192, z = 28, y = -4711.16, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.346712, oz = 0, ow = 0.937972, x = -5049.64, z = 21, y = -2304.52, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.290803, oz = 0, ow = 0.956783, x = 3330.38, z = 308, y = 5517.14, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.666281, oz = 0, ow = 0.745701, x = -136.437, z = 28, y = -4730.23, parentid = 0}
	}
}

dantooine = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Dantooine Mining Outpost", x = -635.96887, z = 3, y = 2507.0115, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Dantooine Imperial Outpost", x = -4208.6602, z = 3, y = -2350.24, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Dantooine Agro Outpost", x = 1569.66, z = 4, y = -6415.7598, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.695864, oz = 0, ow = 0.718174, x = 1585.68, z = 4, y = -6368.95, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.725999, oz = 0, ow = -0.687696, x = -629.417, z = 3, y = 2481.24, parentid = 0}
 	}
}

dathomir = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Trade Outpost", x = 618.89258, z = 6.039608, y = 3092.0142, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Science Outpost", x = -49.021923, z = 18, y = -1584.7278, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1} 
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.701463, oz = 0, ow = 0.712705, x = 592.612, z = 6, y = 3089.84, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.314904, oz = 0, ow = 0.949123, x = -67.6585, z = 18, y = -1595.3, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.314904, oz = 0, ow = 0.949123, x = 5289.6, z = 78.5, y = -4146.1, parentid = 0}
	}
}

endor = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Smuggler Outpost", x = -950.59241, z = 73, y = 1553.4125, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Research Outpost", x = 3201.6599, z = 24, y = -3499.76, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.932952, oz = 0, ow = -0.360002, x = -963.537, z = 73, y = 1556.86, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.723459, oz = 0, ow = -0.690367, x = 3240.5, z = 24, y = -3484.79, parentid = 0},
		-- TEMPORARY
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.723459, oz = 0, ow = -0.690367, x = -4676.78, z = 12.9066, y = 4327.25, parentid = 0}
	}
}

lok = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Nym's Stronghold", x = 478.92676, z = 9, y = 5511.9565, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.999879, oz = 0, ow = 0.015506, x = 464.677, z = 8.75806, y = 5506.49, parentid = 0}
	}
}

naboo = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Keren Starport", x = 1371.5938, z = 13, y = 2747.9043, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Keren Shuttleport South", x = 1567.5193, z = 25, y = 2837.8777, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Keren Shuttleport", x = 2021.0026, z = 19, y = 2525.679, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Theed Shuttle A", x = -5856.1055, z = 6, y = 4172.1606, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Theed Shuttle B", x = -5005, z = 6, y = 4072, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Theed Shuttle C", x = -5411.0171, z = 6, y = 4322.3315, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Theed Spaceport", x = -4858.834, z = 5.9483199, y = 4164.0679, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "The Lake Retreat", x = -5494.4224, z = -150, y = -21.837162, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Moenia", x = 4731.1743, z = 4.1700001, y = -4677.5439, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Moenia Shuttleport", x = 4961.9409, z = 3.75, y = -4892.6997, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Dee'ja Peak Shuttleport", x = 5331.9375, z = 327.02765, y = -1576.6733, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Kaadara Starport", x = 5280.2002, z = -192, y = 6688.0498, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Kaadara Shuttleport", x = 5123.3857, z = -192, y = 6616.0264, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.715602, oz = 0, ow = -0.698509, x = 4824.53, z = 4.17, y = -4704.9, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.309582, oz = 0, ow = 0.950873, x = -4876.99, z = 6, y = 4142.12, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0116238, oz = 0, ow = 0.999932, x = 5193.14, z = -192, y = 6680.25, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0116238, oz = 0, ow = -0.686427, x = 1445.8, z = 13, y = 2771.98, parentid = 0}
	}
}

rori = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Restuss Starport", x = 5340, z = 80, y = 5734, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Restuss Shuttleport", x = 5211, z = 80, y = 5791, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Narmle Starport", x = -5374.0718, z = 80, y = -2188.6143, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Narmle Shuttleport", x = -5255.4116, z = 80.664185, y = -2161.6274, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Rebel Outpost", x = 3691.9023, z = 96, y = -6403.4404, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.100263, oz = 0, ow = 0.994961, x = -5307.37, z = 80.1274, y = -2216.91, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.69192, oz = 0, ow = 0.721974, x = 5370.22, z = 80, y = 5666.04, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.0274543, oz = 0, ow = 0.999623, x = 3672.91, z = 96, y = -6441.07, parentid = 0}
	}
}

talus = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Dearic Starport", x = 263.58401, z = 6, y = -2952.1284, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Dearic Shuttleport", x = 699.297, z = 6, y = -3041.4199, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Talus Imperial Outpost", x = -2226, z = 20, y = 2319, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Nashal Shuttleport", x = 4334.5786, z = 9.8999996, y = 5431.0415, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Nashal Starport", x = 4453.7212, z = 2, y = 5354.3345, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.996369, oz = 0, ow = -0.0851417, x = 4447.08, z = 2, y = 5286.96, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.692641, oz = 0, ow = 0.721282, x = 329.666, z = 6, y = -2924.69, parentid = 0}
	}
}

tatooine = {

	weatherEnabled = 1,
	planetTravelPoints = {
		{name = "Mos Eisley Shuttleport", x = 3416.6914, z = 5, y = -4648.1411, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Eisley Starport", x = 3599.894, z = 5, y = -4780.4487, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Bestine Starport", x = -1361.1917, z = 12, y = -3600.0254, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Bestine Shuttleport", x = -1098.4836, z = 12, y = -3563.5342, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Espa Shuttleport South", x = -2897.0933, z = 5, y = 1933.4144, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Espa Shuttleport West", x = -3112.1296, z = 5, y = 2176.9607, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Espa Starport", x = -2833.1609, z = 5, y = 2107.3787, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Mos Espa Shuttleport East", x = -2803.511, z = 5, y = 2182.9648, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Anchorhead Shuttleport", x = 47.565128, z = 52, y = -5338.9072, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Entha Spaceport", x = 1266.0996, z = 7, y = 3065.1392, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Mos Entha Shuttle B", x = 1395.447, z = 7, y = 3467.0117, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1},
		{name = "Mos Entha Shuttle A", x = 1730.8828, z = 7, y = 3184.6135, interplanetaryTravelAllowed = 0, incomingTravelAllowed = 1}
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.768226, oz = 0, ow = -0.640178, x = 3533.04, z = 5, y = -4796, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.486657, oz = 0, ow = 0.873593, x = -1271.07, z = 12, y = -3590.22, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.514176, oz = 0, ow = 0.857684, x = -2896.35, z = 5, y = 2130.87, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.989124, oz = 0, ow = -0.147086, x = 1299.08, z = 7, y = 3145.21, parentid = 0}
	}
}

yavin4 = {

	weatherEnabled = 1,

	planetTravelPoints = {
		{name = "Yavin IV Labor Outpost", x = -6921.6733, z = 73, y = -5726.5161, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Yavin IV Mining Outpost", x = -267.23914, z = 35, y = 4896.3013, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 1},
		{name = "Yavin IV Imperial Outpost", x = 4054.1, z = 37, y = -6216.9, interplanetaryTravelAllowed = 1, incomingTravelAllowed = 0},
	},
	
	planetObjects = {
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = -0.705623, oz = 0, ow = 0.708587, x = -6917.18, z = 73, y = -5732.25, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.723339, oz = 0, ow = -0.690493, x = 4057.69, z = 37, y = -6217.54, parentid = 0},
		{templateFile = "object/tangible/terminal/terminal_character_builder.iff", ox = 0, oy = 0.00721678, oz = 0, ow = 0.999974, x = -293.367, z = 35, y = 4854.52, parentid = 0}
	}
}

space_corellia = {

	weatherEnabled = 0,
	planetObjects = {
		{templateFile = "object/ship/spacestation_rebel.iff", x = -7132.79, z = 2340.4, y = 2013.98, ow = 0.641545, ox = -0.0633626, oy = 0.76035, oz = 0.079203, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -6345.5, z = -5274.5, y = -3957.25, ow = 0.640802, ox = 0.015822, oy = 0.76738, oz = -0.0158223, parentid = 0},
		{templateFile = "object/ship/spacestation_rebel.iff", x = -1463.42, z = 318.86, y = -1012.24, ow = 0.759136, ox = -0.0474463, oy = 0.648429, oz = 0.0316307, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = 6519.75, z = -5373.75, y = -2600.25, ow = -0.428073, ox = -1.39125e-08, oy = 0.90371, oz = -0.00792732, parentid = 0}
	}
}

space_dantooine = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = -2629.72, z = 3585.8, y = 3269.39, ow = 0.103184, ox = 0.031749, oy = 0.936596, oz = -0.333365, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = 178.72, z = -4785.06, y = -6403.03, ow = 0.977105, ox = 0, oy = 0.212757, oz = 0, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = 1358.93, z = -741.97, y = -5901.79, ow = 0.907314, ox = 0.110455, oy = 0.394484, oz = -0.0946762, parentid = 0},
		{templateFile = "object/ship/spacestation_rebel.iff", x = -4200, z = -3000, y = -6000, ow = 1, ox = 0, oy = 0, oz = 0, parentid = 0},
		{templateFile = "object/ship/spacestation_rebel.iff", x = 5522.87, z = 3202, y = 5997.74, ow = -0.236536, ox = -0.031538, oy = 0.954028, oz = -0.181344, parentid = 0},
		{templateFile = "object/ship/spacestation_rebel.iff", x = -3979.37, z = 5423.26, y = -4565.81, ow = 0.917577, ox = 0.0791015, oy = 0.387597, oz = -0.0395508, parentid = 0}
	}
}

space_dathomir = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = 4842.19, z = -5316.32, y = -4222.79, ow = 0.849126, ox = -0.277752, oy = -0.428531, oz = -0.134908, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = 6092.23, z = 6223.58, y = -6731.9, ow = 0.967128, ox = 0.182327, oy = -0.1744, oz = 0.0317089, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = 4000, z = 200, y = -4700, ow = 1, ox = 0, oy = 0, oz = 0, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -7078.75, z = 2879, y = -4293.75, ow = 0.946438, ox = 0.173514, oy = 0.268158, oz = -0.0473218, parentid = 0}
	}
}

space_endor = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = 5773.37, z = -6359.57, y = 6976.04, ow = 0.197218, ox = -0.0157777, oy = 0.978199, oz = 0.0631097, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = 6200, z = 5000, y = 6000, ow = 1, ox = 0, oy = 0, oz = 0, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = -5716.48, z = 7198.22, y = 2009.09, ow = 0.781614, ox = 0.307908, oy = 0.505286, oz = -0.197377, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -5268.23, z = -1500.23, y = 5209.39, ow = 0.919533, ox = 0.151784, oy = -0.359617, oz = 0.0457911, parentid = 0}
	}
}

space_lok = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = -1798.64, z = 2649.25, y = 400.89, ow = -0.031722, ox = 0.0158608, oy = 0.999245, oz = 0.0158608, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -6235.21, z = -5341.59, y = 113.86, ow = 0.611794, ox = 0.347264, oy = 0.577203, oz = -0.414672, parentid = 0},
		{templateFile = "object/ship/spacestation_rebel.iff", x = 1799.13, z = -2458.57, y = -3680.29, ow = 0.989635, ox = -0.13459, oy = 0.0475025, oz = 0.0158343, parentid = 0}
	}
}

space_naboo = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = 3511.83, z = 1774.71, y = 944.36, ow = -0.670707, ox = 0, oy = 0.741723, oz = 0, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -2491.26, z = 905.49, y = -6460.67, ow = 0.201287, ox = -0.00687047, oy = 0.968212, oz = 0.148333, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = 6226.22, z = -4450.57, y = 484.75, ow = 0.36384, ox = -0.0206368, oy = 0.924935, oz = 0.108118, parentid = 0}
	}
}

space_tatooine = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_neutral.iff", x = 2311.89, z = -5872.72, y = 1865.29, ow = 0.324318, ox = 0.0734025, oy = 0.94172, oz = -0.0509326, parentid = 0}
	}
}

space_yavin4 = {

	weatherEnabled = 0,

	planetObjects = {
		{templateFile = "object/ship/spacestation_imperial.iff", x = -6798.55, z = 4998.69, y = 4760.4, ow = 0.577296, ox = 0.0316324, oy = 0.814541, oz = -0.0474491, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = -4190.56, z = 1539.35, y = 4596.82, ow = 0.434352, ox = 0.023692, oy = 0.900293, oz = -0.0157947, parentid = 0},
		{templateFile = "object/ship/spacestation_imperial.iff", x = 85.21, z = -342.3, y = -57.62, ow = 0.627024, ox = 0.0158741, oy = 0.777827, oz = -0.039685, parentid = 0},
		{templateFile = "object/ship/spacestation_neutral.iff", x = -5570.46, z = -5168, y = -5234.88, ow = 0.994108, ox = 0.105996, oy = -0.0145207, oz = -0.0173906, parentid = 0}
	}
}

tutorial = {
	weatherEnabled = 0,
}

dungeon1 = {
	weatherEnabled = 0,
}
