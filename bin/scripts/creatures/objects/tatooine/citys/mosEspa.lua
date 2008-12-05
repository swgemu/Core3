--Copyright (C) 2008 <SWGEmu>

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

mosEspaNpc1 = Creature:new {
	objectName = "mosEspaNpc1",
	creatureType = NPC,

	speciesName = "tatooine_militiaman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3885288051,
	positionX = -48.9859,
	positionY = 33.6967,
	positionZ = 2.63942,

	directionX = -5.82514e-12,
	directionZ = -1.0837e-07,
	directionY = 1,
	directionW = -5.37526e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261663
}

mosEspaNpc2 = Creature:new {
	objectName = "mosEspaNpc2",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 713507325,
	positionX = -50.0859,
	positionY = 33.6967,
	positionZ = 2.63942,

	directionX = 2.93242e-08,
	directionZ = -7.08015e-08,
	directionY = 0.923892,
	directionW = 0.382653,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261663
}

mosEspaNpc3 = Creature:new {
	objectName = "mosEspaNpc3",
	creatureType = NPC,

	speciesName = "twilek_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 504610439,
	positionX = -29.0928,
	positionY = 51.3406,
	positionZ = 1.63942,

	directionX = -1.19216e-07,
	directionZ = 1.129e-12,
	directionY = 9.53725e-06,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261660
}

mosEspaNpc4 = Creature:new {
	objectName = "mosEspaNpc4",
	creatureType = NPC,

	speciesName = "twilek_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 2157868779,
	positionX = -29.0928,
	positionY = 52.3406,
	positionZ = 1.63942,

	directionX = -5.28058e-12,
	directionZ = -1.7883e-07,
	directionY = 1,
	directionW = -2.95666e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261660
}

mosEspaNpc5 = Creature:new {
	objectName = "mosEspaNpc5",
	creatureType = NPC,

	speciesName = "rodian_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3737467730,
	positionX = 1.1,
	positionY = 66.3,
	positionZ = 0.639421,

	directionX = 0,
	directionZ = -0,
	directionY = 0.284015,
	directionW = 0.95882,
	randomMovement = 0,
	mood = "explain",
	cellID = 1261655
}

mosEspaNpc6 = Creature:new {
	objectName = "mosEspaNpc6",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2500249611,
	positionX = -2881.23,
	positionY = 2004.94,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.894749,
	directionW = -0.44657,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc7 = Creature:new {
	objectName = "mosEspaNpc7",
	creatureType = NPC,

	speciesName = "rel_keteris",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_spawner_n",
	objectCRC = 3956928835,
	positionX = -2905.83,
	positionY = 2127.11,
	positionZ = 5,

	directionX = -0,
	directionZ = 0,
	directionY = 0.790062,
	directionW = -0.613027,
	randomMovement = 0,
	mood = "neutral",
	cellID = 0
}

mosEspaNpc8 = Creature:new {
	objectName = "mosEspaNpc8",
	creatureType = NPC,

	speciesName = "anim_kahn",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_spawner_n",
	objectCRC = 3404283589,
	positionX = -2907.07,
	positionY = 2130.14,
	positionZ = 5,

	directionX = 0.00571667,
	directionZ = 0.00787072,
	directionY = 0.58764,
	directionW = 0.809064,
	randomMovement = 0,
	mood = "neutral",
	cellID = 0
}

mosEspaNpc9 = Creature:new {
	objectName = "mosEspaNpc9",
	creatureType = NPC,

	speciesName = "prost_roberts",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_spawner_n",
	objectCRC = 1419401755,
	positionX = -2906.52,
	positionY = 2128.41,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.613119,
	directionW = 0.78999,
	randomMovement = 0,
	mood = "neutral",
	cellID = 0
}

mosEspaNpc10 = Creature:new {
	objectName = "mosEspaNpc10",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1309761692,
	positionX = -2918.94,
	positionY = 2170.6,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 1,
	directionW = 0,
	randomMovement = 0,
	mood = "conversation",
	cellID = 0
}

mosEspaNpc11 = Creature:new {
	objectName = "mosEspaNpc11",
	creatureType = NPC,

	speciesName = "brawler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3726012530,
	positionX = -2918.94,
	positionY = 2169.6,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 0
}

mosEspaNpc12 = Creature:new {
	objectName = "mosEspaNpc12",
	creatureType = NPC,

	speciesName = "r2",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1584953800,
	positionX = -2928.79,
	positionY = 2111.03,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.841087,
	directionW = -0.5409,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc13 = Creature:new {
	objectName = "mosEspaNpc13",
	creatureType = NPC,

	speciesName = "r5",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2778419932,
	positionX = -2915.25,
	positionY = 2163.42,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.974415,
	directionW = 0.224756,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc14 = Creature:new {
	objectName = "mosEspaNpc14",
	creatureType = NPC,

	speciesName = "cll8_binary_load_lifter",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 103360686,
	positionX = -2922.62,
	positionY = 2143.4,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.170061,
	directionW = 0.985434,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc15 = Creature:new {
	objectName = "mosEspaNpc15",
	creatureType = NPC,

	speciesName = "bestine_artist05",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3927474941,
	positionX = -2768.32,
	positionY = 2110.71,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.664378,
	directionW = 0.747397,
	randomMovement = 0,
	mood = "neutral",
	cellID = 0
}

mosEspaNpc16 = Creature:new {
	objectName = "mosEspaNpc16",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2736.1,
	positionY = 2188.86,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.567551,
	directionW = 0.823338,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc17 = Creature:new {
	objectName = "mosEspaNpc17",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2731.88,
	positionY = 2185.65,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.874902,
	directionW = -0.484299,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc18 = Creature:new {
	objectName = "mosEspaNpc18",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2753395803,
	positionX = -2748.23,
	positionY = 2031.47,
	positionZ = 5,

	directionX = 0,
	directionZ = -0,
	directionY = -0.191037,
	directionW = 0.981583,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc19 = Creature:new {
	objectName = "mosEspaNpc19",
	creatureType = NPC,

	speciesName = "commoner_human_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 402941115,
	positionX = -2909.17,
	positionY = 2180.03,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -1.34017e-08,
	directionW = 1,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc20 = Creature:new {
	objectName = "mosEspaNpc20",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504610439,
	positionX = -2810.65,
	positionY = 2195.86,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.358414,
	directionW = 0.933563,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc21 = Creature:new {
	objectName = "mosEspaNpc21",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2027163053,
	positionX = -2774.25,
	positionY = 2018.1,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.875076,
	directionW = -0.483986,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc22 = Creature:new {
	objectName = "mosEspaNpc22",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2053608249,
	positionX = -2760.75,
	positionY = 2038.95,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.743406,
	directionW = -0.668841,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc23 = Creature:new {
	objectName = "mosEspaNpc23",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 728074066,
	positionX = -2739.74,
	positionY = 2044.75,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.765492,
	directionW = 0.643445,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc24 = Creature:new {
	objectName = "mosEspaNpc24",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2112269243,
	positionX = -2952.26,
	positionY = 2087.58,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.394548,
	directionW = 0.918875,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc25 = Creature:new {
	objectName = "mosEspaNpc25",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 36713428,
	positionX = -2860.36,
	positionY = 2212.37,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.139949,
	directionW = 0.990159,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc26 = Creature:new {
	objectName = "mosEspaNpc26",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2930.03,
	positionY = 2038.02,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.707107,
	directionW = 0.707107,
	randomMovement = 0,
	mood = "conversation",
	cellID = 0
}

mosEspaNpc27 = Creature:new {
	objectName = "mosEspaNpc27",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2932.03,
	positionY = 2038.02,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.707107,
	directionW = 0.707107,
	randomMovement = 0,
	mood = "conversation",
	cellID = 0
}

mosEspaNpc28 = Creature:new {
	objectName = "mosEspaNpc28",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2931.03,
	positionY = 2037.02,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 0
}

mosEspaNpc29 = Creature:new {
	objectName = "mosEspaNpc29",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2009015124,
	positionX = -2924.82,
	positionY = 2143.27,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.895933,
	directionW = 0.444189,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc30 = Creature:new {
	objectName = "mosEspaNpc30",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4103475195,
	positionX = -2881.87,
	positionY = 2142.69,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.163352,
	directionW = 0.986568,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc31 = Creature:new {
	objectName = "mosEspaNpc31",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3726012530,
	positionX = -2919.38,
	positionY = 2143.08,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.465446,
	directionW = 0.885076,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc32 = Creature:new {
	objectName = "mosEspaNpc32",
	creatureType = NPC,

	speciesName = "r4",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3969267025,
	positionX = -2959.44,
	positionY = 2110.92,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.829516,
	directionW = 0.558483,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc33 = Creature:new {
	objectName = "mosEspaNpc33",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.464662,
	directionW = 0.885488,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc34 = Creature:new {
	objectName = "mosEspaNpc34",
	creatureType = NPC,

	speciesName = "jawa_engineer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.666549,
	directionW = 0.745462,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc35 = Creature:new {
	objectName = "mosEspaNpc35",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.333788,
	directionW = 0.942648,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc36 = Creature:new {
	objectName = "mosEspaNpc36",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.885779,
	directionW = -0.464107,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc37 = Creature:new {
	objectName = "mosEspaNpc37",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.464244,
	directionW = 0.885707,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc38 = Creature:new {
	objectName = "mosEspaNpc38",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.257558,
	directionW = 0.966263,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc39 = Creature:new {
	objectName = "mosEspaNpc39",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3336907091,
	positionX = -2715.87,
	positionY = 2040.78,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.952816,
	directionW = 0.30355,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc40 = Creature:new {
	objectName = "mosEspaNpc40",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1395390566,
	positionX = -2767.35,
	positionY = 2232.76,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.991095,
	directionW = 0.133157,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc41 = Creature:new {
	objectName = "mosEspaNpc41",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.464558,
	directionW = 0.885542,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc42 = Creature:new {
	objectName = "mosEspaNpc42",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.463984,
	directionW = 0.885844,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc43 = Creature:new {
	objectName = "mosEspaNpc43",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.775113,
	directionW = -0.631822,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc44 = Creature:new {
	objectName = "mosEspaNpc44",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.464368,
	directionW = 0.885642,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc45 = Creature:new {
	objectName = "mosEspaNpc45",
	creatureType = NPC,

	speciesName = "jawa_engineer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2194.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.484297,
	directionW = 0.874904,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc46 = Creature:new {
	objectName = "mosEspaNpc46",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2726.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.590362,
	directionW = 0.807139,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc47 = Creature:new {
	objectName = "mosEspaNpc47",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.205899,
	directionW = 0.978573,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc48 = Creature:new {
	objectName = "mosEspaNpc48",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.558841,
	directionW = 0.829275,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc49 = Creature:new {
	objectName = "mosEspaNpc49",
	creatureType = NPC,

	speciesName = "jawa_smuggler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.206206,
	directionW = 0.978509,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc50 = Creature:new {
	objectName = "mosEspaNpc50",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.885848,
	directionW = -0.463976,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc51 = Creature:new {
	objectName = "mosEspaNpc51",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.122617,
	directionW = 0.992454,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc52 = Creature:new {
	objectName = "mosEspaNpc52",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2716.76,
	positionY = 2204.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.205784,
	directionW = 0.978598,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc53 = Creature:new {
	objectName = "mosEspaNpc53",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3090816966,
	positionX = -2770.48,
	positionY = 2245.4,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.954212,
	directionW = -0.299132,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc54 = Creature:new {
	objectName = "mosEspaNpc54",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4246267513,
	positionX = -2731.39,
	positionY = 2226.03,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.989732,
	directionW = -0.142935,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc55 = Creature:new {
	objectName = "mosEspaNpc55",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3411344577,
	positionX = -2857.9,
	positionY = 2250.18,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.97951,
	directionW = 0.201396,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc57 = Creature:new {
	objectName = "mosEspaNpc57",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1359439934,
	positionX = -2890.19,
	positionY = 2251.37,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.995859,
	directionW = -0.0909165,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc58 = Creature:new {
	objectName = "mosEspaNpc58",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2082161926,
	positionX = -2960.96,
	positionY = 2163.64,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.63805,
	directionW = 0.769995,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc59 = Creature:new {
	objectName = "mosEspaNpc59",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2257954726,
	positionX = -2969.77,
	positionY = 2194.82,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.987228,
	directionW = -0.159316,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc60 = Creature:new {
	objectName = "mosEspaNpc60",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1110857106,
	positionX = -2927.54,
	positionY = 2013.85,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.32523,
	directionW = 0.945635,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc61 = Creature:new {
	objectName = "mosEspaNpc61",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4244927617,
	positionX = -2954.74,
	positionY = 2235.4,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.895535,
	directionW = -0.444991,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc62 = Creature:new {
	objectName = "mosEspaNpc62",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1640273329,
	positionX = -3000.81,
	positionY = 2213.95,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.96309,
	directionW = 0.26918,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc63 = Creature:new {
	objectName = "mosEspaNpc63",
	creatureType = NPC,

	speciesName = "r5",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2778419932,
	positionX = -2919.36,
	positionY = 2262.73,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.136391,
	directionW = 0.990655,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc64 = Creature:new {
	objectName = "mosEspaNpc64",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 502432196,
	positionX = -2881.81,
	positionY = 2267.41,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.487033,
	directionW = 0.873384,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc65 = Creature:new {
	objectName = "mosEspaNpc65",
	creatureType = NPC,

	speciesName = "r5",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2778419932,
	positionX = -2935.94,
	positionY = 2275.75,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.975387,
	directionW = -0.220499,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc66 = Creature:new {
	objectName = "mosEspaNpc66",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1678307362,
	positionX = -2859.3,
	positionY = 2288.53,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0740837,
	directionW = 0.997252,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc67 = Creature:new {
	objectName = "mosEspaNpc67",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3542800680,
	positionX = -2810.06,
	positionY = 2318.02,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.713321,
	directionW = -0.700838,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc68 = Creature:new {
	objectName = "mosEspaNpc68",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3106175116,
	positionX = -2897.39,
	positionY = 2323.06,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.459749,
	directionW = 0.888049,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc69 = Creature:new {
	objectName = "mosEspaNpc69",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1944026085,
	positionX = -2766.88,
	positionY = 2314.77,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.983056,
	directionW = -0.183304,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc70 = Creature:new {
	objectName = "mosEspaNpc70",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3411344577,
	positionX = -2731.61,
	positionY = 2242.41,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.174254,
	directionW = 0.984701,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc71 = Creature:new {
	objectName = "mosEspaNpc71",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2753395803,
	positionX = -2794.64,
	positionY = 2327.09,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.817596,
	directionW = 0.575792,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc72 = Creature:new {
	objectName = "mosEspaNpc72",
	creatureType = NPC,

	speciesName = "crackdown_imperial_noncom",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -2673.96,
	positionY = 2275.9,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.015079,
	directionW = 0.999886,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc73 = Creature:new {
	objectName = "mosEspaNpc73",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -2684.7,
	positionY = 2033.1,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.19336,
	directionW = 0.981128,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc74 = Creature:new {
	objectName = "mosEspaNpc74",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1359439934,
	positionX = -2722.49,
	positionY = 2007.18,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.946981,
	directionW = -0.321289,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc75 = Creature:new {
	objectName = "mosEspaNpc75",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4246267513,
	positionX = -2754.28,
	positionY = 1981.64,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.733154,
	directionW = 0.680063,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc76 = Creature:new {
	objectName = "mosEspaNpc76",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2595.01,
	positionY = 2036.52,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.813752,
	directionW = 0.581212,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc77 = Creature:new {
	objectName = "mosEspaNpc77",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2633.87,
	positionY = 1974.12,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.999972,
	directionW = -0.00753232,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc78 = Creature:new {
	objectName = "mosEspaNpc78",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2747508026,
	positionX = -2787.25,
	positionY = 1962.04,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.129657,
	directionW = 0.991559,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc79 = Creature:new {
	objectName = "mosEspaNpc79",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2593.9,
	positionY = 2038.48,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.984105,
	directionW = 0.177587,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc81 = Creature:new {
	objectName = "mosEspaNpc81",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2591.62,
	positionY = 2039.11,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.274838,
	directionW = 0.961491,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc82 = Creature:new {
	objectName = "mosEspaNpc82",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2599.47,
	positionY = 2034.19,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.823305,
	directionW = -0.5676,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc83 = Creature:new {
	objectName = "mosEspaNpc83",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2577.03,
	positionY = 2056.68,
	positionZ = 5.28616,

	directionX = 0,
	directionZ = 0,
	directionY = -0.165893,
	directionW = 0.986144,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc85 = Creature:new {
	objectName = "mosEspaNpc85",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2626.73,
	positionY = 1962.54,
	positionZ = 5.0133,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0838752,
	directionW = 0.996476,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc91 = Creature:new {
	objectName = "mosEspaNpc91",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2590.42,
	positionY = 2212.03,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.995188,
	directionW = 0.0979806,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc95 = Creature:new {
	objectName = "mosEspaNpc95",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2493.23,
	positionY = 2113.18,
	positionZ = 6.82684,

	directionX = 0,
	directionZ = 0,
	directionY = -0.539021,
	directionW = 0.842292,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc97 = Creature:new {
	objectName = "mosEspaNpc97",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2491.39,
	positionY = 2156.44,
	positionZ = 6.83135,

	directionX = 0,
	directionZ = 0,
	directionY = -0.191602,
	directionW = 0.981473,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc98 = Creature:new {
	objectName = "mosEspaNpc98",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2485.06,
	positionY = 2153.94,
	positionZ = 7.15469,

	directionX = 0,
	directionZ = 0,
	directionY = 0.949605,
	directionW = 0.313448,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc99 = Creature:new {
	objectName = "mosEspaNpc99",
	creatureType = NPC,

	speciesName = "crackdown_elite_dark_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1312348723,
	positionX = -2658.16,
	positionY = 2252.08,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.986016,
	directionW = -0.166653,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc100 = Creature:new {
	objectName = "mosEspaNpc100",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2593.13,
	positionY = 2213.37,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.944881,
	directionW = 0.327414,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc101 = Creature:new {
	objectName = "mosEspaNpc101",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2594.47,
	positionY = 2219.41,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.980362,
	directionW = -0.197208,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc102 = Creature:new {
	objectName = "mosEspaNpc102",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2601.23,
	positionY = 2320.44,
	positionZ = 5.0058,

	directionX = 0,
	directionZ = 0,
	directionY = 0.947512,
	directionW = -0.319719,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc104 = Creature:new {
	objectName = "mosEspaNpc104",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2599.04,
	positionY = 2338.05,
	positionZ = 5.20143,

	directionX = 0,
	directionZ = 0,
	directionY = 0.379795,
	directionW = 0.925071,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc105 = Creature:new {
	objectName = "mosEspaNpc105",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2592.54,
	positionY = 2333.19,
	positionZ = 5.37076,

	directionX = 0,
	directionZ = 0,
	directionY = 0.994858,
	directionW = -0.101279,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc106 = Creature:new {
	objectName = "mosEspaNpc106",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2591.43,
	positionY = 2342.79,
	positionZ = 5.32223,

	directionX = 0,
	directionZ = 0,
	directionY = 0.720011,
	directionW = -0.693963,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc112 = Creature:new {
	objectName = "mosEspaNpc112",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3627678729,
	positionX = -2818.45,
	positionY = 2407.94,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.873182,
	directionW = -0.487394,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc119 = Creature:new {
	objectName = "mosEspaNpc119",
	creatureType = NPC,

	speciesName = "desert_demon",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 783797004,
	positionX = -2821.38,
	positionY = 2432.95,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.999536,
	directionW = 0.0304693,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc120 = Creature:new {
	objectName = "mosEspaNpc120",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3848890772,
	positionX = -2847.77,
	positionY = 2393.35,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.358832,
	directionW = 0.933402,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc121 = Creature:new {
	objectName = "mosEspaNpc121",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3221946711,
	positionX = -2837.3,
	positionY = 2425.05,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.79817,
	directionW = -0.602433,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc123 = Creature:new {
	objectName = "mosEspaNpc123",
	creatureType = NPC,

	speciesName = "desert_demon",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 124777914,
	positionX = -2823.03,
	positionY = 2448.69,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.532938,
	directionW = 0.846154,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc127 = Creature:new {
	objectName = "mosEspaNpc127",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1903416078,
	positionX = -2834.04,
	positionY = 2462.23,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.992892,
	directionW = -0.119022,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc128 = Creature:new {
	objectName = "mosEspaNpc128",
	creatureType = NPC,

	speciesName = "desert_demon",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 124777914,
	positionX = -2861.27,
	positionY = 2393.34,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.95846,
	directionW = 0.285228,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc135 = Creature:new {
	objectName = "mosEspaNpc135",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3869730090,
	positionX = -2839.04,
	positionY = 2492.89,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.464647,
	directionW = 0.885496,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc136 = Creature:new {
	objectName = "mosEspaNpc136",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3327481604,
	positionX = -2846.59,
	positionY = 2497.64,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.240878,
	directionW = 0.970555,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc139 = Creature:new {
	objectName = "mosEspaNpc139",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1852970812,
	positionX = -2877.18,
	positionY = 2473.48,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.545776,
	directionW = 0.837931,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc140 = Creature:new {
	objectName = "mosEspaNpc140",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2889.69,
	positionY = 2493.44,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.707286,
	directionW = -0.706928,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc141 = Creature:new {
	objectName = "mosEspaNpc141",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2317265825,
	positionX = -2870.12,
	positionY = 2494.38,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.531836,
	directionW = 0.846847,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc144 = Creature:new {
	objectName = "mosEspaNpc144",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 603795137,
	positionX = -2894.24,
	positionY = 2492.22,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.671853,
	directionW = 0.740685,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc147 = Creature:new {
	objectName = "mosEspaNpc147",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2888.64,
	positionY = 2498.06,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.447691,
	directionW = 0.894188,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc148 = Creature:new {
	objectName = "mosEspaNpc148",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3044338694,
	positionX = -2860.55,
	positionY = 2534.77,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.916565,
	directionW = -0.399887,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc150 = Creature:new {
	objectName = "mosEspaNpc150",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3504184450,
	positionX = -2874.25,
	positionY = 2546.29,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.878382,
	directionW = 0.477959,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc151 = Creature:new {
	objectName = "mosEspaNpc151",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1270757117,
	positionX = -2884.43,
	positionY = 2575.51,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.299689,
	directionW = 0.954037,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc152 = Creature:new {
	objectName = "mosEspaNpc152",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 438738923,
	positionX = -2914.09,
	positionY = 2466.26,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.989541,
	directionW = 0.144249,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc153 = Creature:new {
	objectName = "mosEspaNpc153",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1616396794,
	positionX = -2856.83,
	positionY = 2473.55,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.999333,
	directionW = -0.0365217,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc154 = Creature:new {
	objectName = "mosEspaNpc154",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2888,
	positionY = 2591,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.711622,
	directionW = 0.702563,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc156 = Creature:new {
	objectName = "mosEspaNpc156",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4127988119,
	positionX = -2931.98,
	positionY = 2495.44,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.730918,
	directionW = -0.682465,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc157 = Creature:new {
	objectName = "mosEspaNpc157",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1153411498,
	positionX = -2913.31,
	positionY = 2566.89,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.993802,
	directionW = 0.111164,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc158 = Creature:new {
	objectName = "mosEspaNpc158",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2863.93,
	positionY = 2645.23,
	positionZ = 5.69244,

	directionX = 0,
	directionZ = 0,
	directionY = 0.992749,
	directionW = -0.120202,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc160 = Creature:new {
	objectName = "mosEspaNpc160",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2868.66,
	positionY = 2659.77,
	positionZ = 5.92974,

	directionX = 0,
	directionZ = 0,
	directionY = -0.637964,
	directionW = 0.770067,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc161 = Creature:new {
	objectName = "mosEspaNpc161",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2883.89,
	positionY = 2636.44,
	positionZ = 5.34137,

	directionX = 0,
	directionZ = 0,
	directionY = 0.943936,
	directionW = -0.330128,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc163 = Creature:new {
	objectName = "mosEspaNpc163",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2879.16,
	positionY = 2642.48,
	positionZ = 5.3938,

	directionX = 0,
	directionZ = 0,
	directionY = 0.969208,
	directionW = -0.246243,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc164 = Creature:new {
	objectName = "mosEspaNpc164",
	creatureType = NPC,

	speciesName = "coa2_rebel_coordinator",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3881299181,
	positionX = -2927.64,
	positionY = 2574.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.466204,
	directionW = 0.884677,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc165 = Creature:new {
	objectName = "mosEspaNpc165",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2871.32,
	positionY = 2638.84,
	positionZ = 5.43329,

	directionX = 0,
	directionZ = 0,
	directionY = 0.994119,
	directionW = 0.108293,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc167 = Creature:new {
	objectName = "mosEspaNpc167",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2558798248,
	positionX = -2964.35,
	positionY = 2536.74,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.844523,
	directionW = -0.53552,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc169 = Creature:new {
	objectName = "mosEspaNpc169",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2958.99,
	positionY = 2651.86,
	positionZ = 6.05473,

	directionX = 0,
	directionZ = 0,
	directionY = 0.305099,
	directionW = 0.952321,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc171 = Creature:new {
	objectName = "mosEspaNpc171",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2954.14,
	positionY = 2648.89,
	positionZ = 5.93401,

	directionX = 0,
	directionZ = 0,
	directionY = 0.645667,
	directionW = 0.763619,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc172 = Creature:new {
	objectName = "mosEspaNpc172",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2909.86,
	positionY = 2692.86,
	positionZ = 7.8253,

	directionX = 0,
	directionZ = 0,
	directionY = 0.797472,
	directionW = 0.603356,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc173 = Creature:new {
	objectName = "mosEspaNpc173",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2957.17,
	positionY = 2663.78,
	positionZ = 6.65151,

	directionX = 0,
	directionZ = 0,
	directionY = 0.983774,
	directionW = -0.17941,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc174 = Creature:new {
	objectName = "mosEspaNpc174",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2977.98,
	positionY = 2651.49,
	positionZ = 5.61491,

	directionX = 0,
	directionZ = 0,
	directionY = 0.949732,
	directionW = -0.313063,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc175 = Creature:new {
	objectName = "mosEspaNpc175",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2959.73,
	positionY = 2662.19,
	positionZ = 6.48665,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0729292,
	directionW = 0.997337,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc176 = Creature:new {
	objectName = "mosEspaNpc176",
	creatureType = NPC,

	speciesName = "criminal",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2121620877,
	positionX = -2976.77,
	positionY = 2539.28,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.310058,
	directionW = 0.950718,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc177 = Creature:new {
	objectName = "mosEspaNpc177",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2922.41,
	positionY = 2711.74,
	positionZ = 8.03007,

	directionX = 0,
	directionZ = 0,
	directionY = -0.295648,
	directionW = 0.955297,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc178 = Creature:new {
	objectName = "mosEspaNpc178",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2921.7,
	positionY = 2717.75,
	positionZ = 7.7918,

	directionX = 0,
	directionZ = 0,
	directionY = -0.190747,
	directionW = 0.981639,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc179 = Creature:new {
	objectName = "mosEspaNpc179",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2909.38,
	positionY = 2704.39,
	positionZ = 7.75577,

	directionX = 0,
	directionZ = 0,
	directionY = 0.787846,
	directionW = -0.615872,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc180 = Creature:new {
	objectName = "mosEspaNpc180",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -3028.33,
	positionY = 2616.08,
	positionZ = 5.01162,

	directionX = 0,
	directionZ = 0,
	directionY = -0.537904,
	directionW = 0.843006,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc181 = Creature:new {
	objectName = "mosEspaNpc181",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4162283815,
	positionX = -3018.71,
	positionY = 2618.52,
	positionZ = 5.01489,

	directionX = 0,
	directionZ = 0,
	directionY = 0.718171,
	directionW = -0.695867,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc182 = Creature:new {
	objectName = "mosEspaNpc182",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3372188319,
	positionX = -3022.29,
	positionY = 2618.41,
	positionZ = 5.02759,

	directionX = 0,
	directionZ = 0,
	directionY = 0.718173,
	directionW = -0.695864,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc183 = Creature:new {
	objectName = "mosEspaNpc183",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1189502506,
	positionX = -3023.26,
	positionY = 2618.44,
	positionZ = 5.04215,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0226668,
	directionW = 0.999743,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc185 = Creature:new {
	objectName = "mosEspaNpc185",
	creatureType = NPC,

	speciesName = "crackdown_imperial_noncom",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -3027.01,
	positionY = 2617.66,
	positionZ = 5.06395,

	directionX = 0,
	directionZ = 0,
	directionY = -0.580428,
	directionW = 0.814312,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc186 = Creature:new {
	objectName = "mosEspaNpc186",
	creatureType = NPC,

	speciesName = "crackdown_imperial_master_sergeant",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -3029.53,
	positionY = 2617.06,
	positionZ = 5.07697,

	directionX = 0,
	directionZ = 0,
	directionY = 0.339982,
	directionW = 0.940432,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc187 = Creature:new {
	objectName = "mosEspaNpc187",
	creatureType = NPC,

	speciesName = "crackdown_dark_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1312348723,
	positionX = -3028.58,
	positionY = 2618.21,
	positionZ = 5.11515,

	directionX = 0,
	directionZ = 0,
	directionY = 0.338923,
	directionW = 0.940814,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc188 = Creature:new {
	objectName = "mosEspaNpc188",
	creatureType = NPC,

	speciesName = "crackdown_scout_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2303490976,
	positionX = -3028.51,
	positionY = 2618.18,
	positionZ = 5.11262,

	directionX = 0,
	directionZ = 0,
	directionY = -0.580456,
	directionW = 0.814292,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc189 = Creature:new {
	objectName = "mosEspaNpc189",
	creatureType = NPC,

	speciesName = "crackdown_stormtrooper_captain",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2493178409,
	positionX = -3026.34,
	positionY = 2618.73,
	positionZ = 5.10198,

	directionX = 0,
	directionZ = 0,
	directionY = -0.580428,
	directionW = 0.814312,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc190 = Creature:new {
	objectName = "mosEspaNpc190",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2963.31,
	positionY = 2664.35,
	positionZ = 6.41839,

	directionX = 0,
	directionZ = 0,
	directionY = 0.168263,
	directionW = 0.985742,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc193 = Creature:new {
	objectName = "mosEspaNpc193",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3006.66,
	positionY = 2697.94,
	positionZ = 7.83559,

	directionX = 0,
	directionZ = 0,
	directionY = 0.838528,
	directionW = -0.544859,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc200 = Creature:new {
	objectName = "mosEspaNpc200",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3126739438,
	positionX = -2978.76,
	positionY = 2473.24,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0514409,
	directionW = 0.998676,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc201 = Creature:new {
	objectName = "mosEspaNpc201",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3080.79,
	positionY = 2611.32,
	positionZ = 6.03743,

	directionX = 0,
	directionZ = 0,
	directionY = -0.678198,
	directionW = 0.734879,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc202 = Creature:new {
	objectName = "mosEspaNpc202",
	creatureType = NPC,

	speciesName = "r2",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1584953800,
	positionX = -2946.98,
	positionY = 2470.9,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0792702,
	directionW = 0.996853,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc203 = Creature:new {
	objectName = "mosEspaNpc203",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -2945.98,
	positionY = 2470.9,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.998455,
	directionW = -0.0555664,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc204 = Creature:new {
	objectName = "mosEspaNpc204",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -2946.98,
	positionY = 2470.9,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.996112,
	directionW = 0.0880922,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc205 = Creature:new {
	objectName = "mosEspaNpc205",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1223887816,
	positionX = -2969.78,
	positionY = 2469.4,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.486745,
	directionW = 0.873544,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc206 = Creature:new {
	objectName = "mosEspaNpc206",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1850887803,
	positionX = -2977.55,
	positionY = 2458.29,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.495393,
	directionW = 0.868669,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc207 = Creature:new {
	objectName = "mosEspaNpc207",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4127988119,
	positionX = -3068.4,
	positionY = 2391.3,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.924667,
	directionW = 0.380776,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc211 = Creature:new {
	objectName = "mosEspaNpc211",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3238.87,
	positionY = 2231.04,
	positionZ = 6.19092,

	directionX = 0,
	directionZ = 0,
	directionY = -0.391772,
	directionW = 0.920062,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc215 = Creature:new {
	objectName = "mosEspaNpc215",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3238.91,
	positionY = 2230.72,
	positionZ = 6.14088,

	directionX = 0,
	directionZ = 0,
	directionY = 0.783183,
	directionW = 0.621791,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc218 = Creature:new {
	objectName = "mosEspaNpc218",
	creatureType = NPC,

	speciesName = "crackdown_imperial_master_sergeant",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1040681339,
	positionX = -3150.22,
	positionY = 2206.83,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.763512,
	directionW = -0.645794,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc220 = Creature:new {
	objectName = "mosEspaNpc220",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3246.28,
	positionY = 2218.4,
	positionZ = 5.42038,

	directionX = 0,
	directionZ = 0,
	directionY = 0.906801,
	directionW = 0.421559,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc225 = Creature:new {
	objectName = "mosEspaNpc225",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -3169.56,
	positionY = 2176.48,
	positionZ = 5,

	directionX = 0.000927453,
	directionZ = 0.000389157,
	directionY = 0.288747,
	directionW = 0.957405,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc227 = Creature:new {
	objectName = "mosEspaNpc227",
	creatureType = NPC,

	speciesName = "crackdown_imperial_master_sergeant",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1040681339,
	positionX = -3204.52,
	positionY = 2091.93,
	positionZ = 5,

	directionX = 0.00285075,
	directionZ = 0.000633426,
	directionY = 0.97791,
	directionW = -0.209009,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc229 = Creature:new {
	objectName = "mosEspaNpc229",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3244.16,
	positionY = 2232.65,
	positionZ = 6.56426,

	directionX = 0,
	directionZ = 0,
	directionY = 0.968766,
	directionW = 0.247975,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc230 = Creature:new {
	objectName = "mosEspaNpc230",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3321.67,
	positionY = 2207.22,
	positionZ = 8.2476,

	directionX = 0,
	directionZ = 0,
	directionY = -0.638004,
	directionW = 0.770033,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc238 = Creature:new {
	objectName = "mosEspaNpc238",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3321.03,
	positionY = 2187.04,
	positionZ = 6.78999,

	directionX = 0,
	directionZ = 0,
	directionY = 0.871925,
	directionW = 0.48964,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc239 = Creature:new {
	objectName = "mosEspaNpc239",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3316.94,
	positionY = 2198.91,
	positionZ = 8.07518,

	directionX = 0,
	directionZ = 0,
	directionY = 0.994063,
	directionW = 0.108804,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc245 = Creature:new {
	objectName = "mosEspaNpc245",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3246.74,
	positionY = 2121.66,
	positionZ = 5.19249,

	directionX = 0,
	directionZ = 0,
	directionY = 0.987669,
	directionW = 0.156556,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc249 = Creature:new {
	objectName = "mosEspaNpc249",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3248.78,
	positionY = 2122.05,
	positionZ = 5.22997,

	directionX = 0,
	directionZ = 0,
	directionY = 0.907554,
	directionW = 0.419936,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc251 = Creature:new {
	objectName = "mosEspaNpc251",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3248.94,
	positionY = 2116.77,
	positionZ = 5.4228,

	directionX = -0,
	directionZ = 0,
	directionY = -0.14263,
	directionW = 0.989776,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc252 = Creature:new {
	objectName = "mosEspaNpc252",
	creatureType = NPC,

	speciesName = "bestine_artist03",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1492569700,
	positionX = -3101.7,
	positionY = 2184.81,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.380072,
	directionW = 0.924957,
	randomMovement = 0,
	mood = "neutral",
	cellID = 0
}

mosEspaNpc253 = Creature:new {
	objectName = "mosEspaNpc253",
	creatureType = NPC,

	speciesName = "crackdown_imperial_warrant_officer_ii",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -3207,
	positionY = 2097.52,
	positionZ = 5,

	directionX = -0.00018288,
	directionZ = -0.0027596,
	directionY = -0.105494,
	directionW = 0.994416,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc256 = Creature:new {
	objectName = "mosEspaNpc256",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 117165421,
	positionX = -3100.44,
	positionY = 2148.76,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.983064,
	directionW = 0.18326,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc257 = Creature:new {
	objectName = "mosEspaNpc257",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3265.58,
	positionY = 2129.95,
	positionZ = 5.20889,

	directionX = 0,
	directionZ = 0,
	directionY = -0.534789,
	directionW = 0.844985,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc258 = Creature:new {
	objectName = "mosEspaNpc258",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1424150563,
	positionX = -3091.67,
	positionY = 2165.61,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.596634,
	directionW = 0.802513,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc261 = Creature:new {
	objectName = "mosEspaNpc261",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3208.98,
	positionY = 2017.03,
	positionZ = 6.12053,

	directionX = 0,
	directionZ = 0,
	directionY = 0.857841,
	directionW = 0.513915,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc262 = Creature:new {
	objectName = "mosEspaNpc262",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2571425416,
	positionX = -3115.34,
	positionY = 2084.32,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.612384,
	directionW = 0.79056,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc263 = Creature:new {
	objectName = "mosEspaNpc263",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3217.87,
	positionY = 2010.86,
	positionZ = 6.7851,

	directionX = -0,
	directionZ = 0,
	directionY = -0.263362,
	directionW = 0.964697,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc266 = Creature:new {
	objectName = "mosEspaNpc266",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3205.35,
	positionY = 2016.06,
	positionZ = 6.01035,

	directionX = 0,
	directionZ = 0,
	directionY = 0.279164,
	directionW = 0.960243,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc267 = Creature:new {
	objectName = "mosEspaNpc267",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3204.49,
	positionY = 2015.95,
	positionZ = 5.96378,

	directionX = 0,
	directionZ = 0,
	directionY = 0.311329,
	directionW = 0.950302,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc268 = Creature:new {
	objectName = "mosEspaNpc268",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3210.83,
	positionY = 2005.31,
	positionZ = 6.40006,

	directionX = 0,
	directionZ = 0,
	directionY = -0.316444,
	directionW = 0.948611,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc273 = Creature:new {
	objectName = "mosEspaNpc273",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3224.53,
	positionY = 1931.72,
	positionZ = 4.79097,

	directionX = 0,
	directionZ = 0,
	directionY = 0.984053,
	directionW = 0.177874,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc274 = Creature:new {
	objectName = "mosEspaNpc274",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504610439,
	positionX = -3081.03,
	positionY = 2104.52,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.158879,
	directionW = 0.987298,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc275 = Creature:new {
	objectName = "mosEspaNpc275",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3177.72,
	positionY = 1907.34,
	positionZ = 8.08039,

	directionX = 0,
	directionZ = 0,
	directionY = -0.204045,
	directionW = 0.978962,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc276 = Creature:new {
	objectName = "mosEspaNpc276",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3243.03,
	positionY = 1922.89,
	positionZ = 5.88032,

	directionX = 0,
	directionZ = 0,
	directionY = 0.998638,
	directionW = -0.052181,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc279 = Creature:new {
	objectName = "mosEspaNpc279",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3173.18,
	positionY = 1901.38,
	positionZ = 8.36948,

	directionX = 0,
	directionZ = 0,
	directionY = -0.49298,
	directionW = 0.870041,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc280 = Creature:new {
	objectName = "mosEspaNpc280",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1222455669,
	positionX = -3060.27,
	positionY = 2085.37,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.998214,
	directionW = -0.0597372,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc281 = Creature:new {
	objectName = "mosEspaNpc281",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3114.39,
	positionY = 1906.64,
	positionZ = 5.75482,

	directionX = 0,
	directionZ = 0,
	directionY = 0.88564,
	directionW = -0.464372,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc282 = Creature:new {
	objectName = "mosEspaNpc282",
	creatureType = NPC,

	speciesName = "minor_worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3096.16,
	positionY = 1913.67,
	positionZ = 5.08975,

	directionX = 0,
	directionZ = 0,
	directionY = 0.994248,
	directionW = 0.107104,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc283 = Creature:new {
	objectName = "mosEspaNpc283",
	creatureType = NPC,

	speciesName = "minor_worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3108.76,
	positionY = 1910.17,
	positionZ = 5.45396,

	directionX = 0,
	directionZ = 0,
	directionY = 0.058845,
	directionW = 0.998267,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc284 = Creature:new {
	objectName = "mosEspaNpc284",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -3172.01,
	positionY = 1888.24,
	positionZ = 8.51885,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0181989,
	directionW = 0.999835,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc285 = Creature:new {
	objectName = "mosEspaNpc285",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -3174.62,
	positionY = 1889.76,
	positionZ = 8.58522,

	directionX = 0,
	directionZ = 0,
	directionY = -0.67167,
	directionW = 0.740851,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc287 = Creature:new {
	objectName = "mosEspaNpc287",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -3093.11,
	positionY = 1912.45,
	positionZ = 5.06432,

	directionX = 0.00557938,
	directionZ = 0.00901523,
	directionY = 0.856131,
	directionW = 0.51665,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc288 = Creature:new {
	objectName = "mosEspaNpc288",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -2985.75,
	positionY = 1978.7,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.60521,
	directionW = 0.796066,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc289 = Creature:new {
	objectName = "mosEspaNpc289",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -2988.1,
	positionY = 1978.04,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.605211,
	directionW = 0.796065,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc290 = Creature:new {
	objectName = "mosEspaNpc290",
	creatureType = NPC,

	speciesName = "crackdown_scout_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2303490976,
	positionX = -2984.22,
	positionY = 1987.49,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.789777,
	directionW = -0.613394,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc291 = Creature:new {
	objectName = "mosEspaNpc291",
	creatureType = NPC,

	speciesName = "crackdown_stormtrooper_squad_leader",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2493178409,
	positionX = -2980.41,
	positionY = 1959.34,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.159617,
	directionW = 0.987179,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc292 = Creature:new {
	objectName = "mosEspaNpc292",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3095.72,
	positionY = 1915.26,
	positionZ = 5.05761,

	directionX = 0,
	directionZ = 0,
	directionY = 0.560372,
	directionW = 0.828241,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc293 = Creature:new {
	objectName = "mosEspaNpc293",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3103.38,
	positionY = 1918.82,
	positionZ = 5.15501,

	directionX = 0,
	directionZ = 0,
	directionY = 0.771287,
	directionW = -0.636487,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc294 = Creature:new {
	objectName = "mosEspaNpc294",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -3113.6,
	positionY = 1908.34,
	positionZ = 5.65245,

	directionX = 0,
	directionZ = 0,
	directionY = 0.303944,
	directionW = 0.95269,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc295 = Creature:new {
	objectName = "mosEspaNpc295",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -2970.81,
	positionY = 1981.34,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.990938,
	directionW = 0.134318,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc296 = Creature:new {
	objectName = "mosEspaNpc296",
	creatureType = NPC,

	speciesName = "crackdown_comm_operator",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1476291957,
	positionX = -2970.64,
	positionY = 1980.73,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.990962,
	directionW = 0.134142,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc297 = Creature:new {
	objectName = "mosEspaNpc297",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2474359135,
	positionX = -2976.17,
	positionY = 2009.31,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.996923,
	directionW = 0.0783858,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc298 = Creature:new {
	objectName = "mosEspaNpc298",
	creatureType = NPC,

	speciesName = "crackdown_sand_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 440719956,
	positionX = -2971.83,
	positionY = 1980.42,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.798925,
	directionW = -0.601431,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc299 = Creature:new {
	objectName = "mosEspaNpc299",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3372188319,
	positionX = -2977.32,
	positionY = 2010.1,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.996922,
	directionW = 0.078402,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc300 = Creature:new {
	objectName = "mosEspaNpc300",
	creatureType = NPC,

	speciesName = "mos_espa_police_officer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2257704323,
	positionX = -2976.54,
	positionY = 2011.63,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.996924,
	directionW = 0.0783796,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc301 = Creature:new {
	objectName = "mosEspaNpc301",
	creatureType = NPC,

	speciesName = "crackdown_elite_dark_trooper",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1312348723,
	positionX = -2953.88,
	positionY = 1933.16,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.134653,
	directionW = 0.990893,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc302 = Creature:new {
	objectName = "mosEspaNpc302",
	creatureType = NPC,

	speciesName = "crackdown_imperial_master_sergeant",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 519244536,
	positionX = -2954.65,
	positionY = 1935.93,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.13467,
	directionW = 0.99089,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

mosEspaNpc303 = Creature:new {
	objectName = "mosEspaNpc303",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4029226753,
	positionX = -2939.1,
	positionY = 1962.9,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.138804,
	directionW = 0.99032,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc304 = Creature:new {
	objectName = "mosEspaNpc304",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3787830527,
	positionX = -2912.23,
	positionY = 1928.7,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.191462,
	directionW = 0.9815,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc305 = Creature:new {
	objectName = "mosEspaNpc305",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -2928.04,
	positionY = 1977.68,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.253558,
	directionW = 0.96732,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc307 = Creature:new {
	objectName = "mosEspaNpc307",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 675581684,
	positionX = -2831.34,
	positionY = 1912.49,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.94692,
	directionW = -0.32147,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc308 = Creature:new {
	objectName = "mosEspaNpc308",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -2833.22,
	positionY = 1899.71,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.843378,
	directionW = -0.53732,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc309 = Creature:new {
	objectName = "mosEspaNpc309",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3043344299,
	positionX = -2881.87,
	positionY = 1974.41,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.266983,
	directionW = 0.963701,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc310 = Creature:new {
	objectName = "mosEspaNpc310",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 849589762,
	positionX = -2815.58,
	positionY = 1940.55,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.215212,
	directionW = 0.976567,
	randomMovement = 0,
	mood = "",
	cellID = 0
}

mosEspaNpc312 = Creature:new {
	objectName = "mosEspaNpc312",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2789.62,
	positionY = 1763.98,
	positionZ = 6.17824,

	directionX = 0,
	directionZ = 0,
	directionY = 0.757826,
	directionW = 0.652457,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc313 = Creature:new {
	objectName = "mosEspaNpc313",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2797.01,
	positionY = 1764.85,
	positionZ = 5.38467,

	directionX = 0,
	directionZ = -0,
	directionY = -0.122886,
	directionW = 0.992421,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc314 = Creature:new {
	objectName = "mosEspaNpc314",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.814191,
	directionW = 0.580598,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc315 = Creature:new {
	objectName = "mosEspaNpc315",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.788997,
	directionW = -0.614397,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc316 = Creature:new {
	objectName = "mosEspaNpc316",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.971217,
	directionW = -0.238195,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc317 = Creature:new {
	objectName = "mosEspaNpc317",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.989818,
	directionW = -0.142337,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc318 = Creature:new {
	objectName = "mosEspaNpc318",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 706793692,
	positionX = -2807.11,
	positionY = 1953.71,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.340995,
	directionW = 0.940065,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc320 = Creature:new {
	objectName = "mosEspaNpc320",
	creatureType = NPC,

	speciesName = "mound_mite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2791.98,
	positionY = 1759.43,
	positionZ = 6.24406,

	directionX = 0,
	directionZ = 0,
	directionY = 0.818373,
	directionW = -0.574687,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc321 = Creature:new {
	objectName = "mosEspaNpc321",
	creatureType = NPC,

	speciesName = "jawa_engineer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.565786,
	directionW = 0.824552,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc322 = Creature:new {
	objectName = "mosEspaNpc322",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.103118,
	directionW = 0.994669,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc323 = Creature:new {
	objectName = "mosEspaNpc323",
	creatureType = NPC,

	speciesName = "jawa_smuggler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.888111,
	directionW = -0.459629,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc324 = Creature:new {
	objectName = "mosEspaNpc324",
	creatureType = NPC,

	speciesName = "jawa_henchman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.852862,
	directionW = -0.522136,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc325 = Creature:new {
	objectName = "mosEspaNpc325",
	creatureType = NPC,

	speciesName = "jawa_engineer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.951872,
	directionW = 0.306497,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc326 = Creature:new {
	objectName = "mosEspaNpc326",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.960807,
	directionW = 0.277217,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc327 = Creature:new {
	objectName = "mosEspaNpc327",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.923602,
	directionW = -0.383352,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc328 = Creature:new {
	objectName = "mosEspaNpc328",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1927.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.888084,
	directionW = -0.459681,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc329 = Creature:new {
	objectName = "mosEspaNpc329",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.812533,
	directionW = -0.582915,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc330 = Creature:new {
	objectName = "mosEspaNpc330",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.0862751,
	directionW = 0.996271,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc331 = Creature:new {
	objectName = "mosEspaNpc331",
	creatureType = NPC,

	speciesName = "jawa_thief",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0344335,
	directionW = 0.999407,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc332 = Creature:new {
	objectName = "mosEspaNpc332",
	creatureType = NPC,

	speciesName = "jawa_smuggler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.997061,
	directionW = 0.0766061,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc333 = Creature:new {
	objectName = "mosEspaNpc333",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.168516,
	directionW = 0.985699,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc334 = Creature:new {
	objectName = "mosEspaNpc334",
	creatureType = NPC,

	speciesName = "jawa",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2767.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.616063,
	directionW = 0.787697,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc335 = Creature:new {
	objectName = "mosEspaNpc335",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.696862,
	directionW = 0.717205,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc336 = Creature:new {
	objectName = "mosEspaNpc336",
	creatureType = NPC,

	speciesName = "jawa_healer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3444186231,
	positionX = -2777.56,
	positionY = 1937.17,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.217768,
	directionW = 0.976,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc339 = Creature:new {
	objectName = "mosEspaNpc339",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2720.95,
	positionY = 1838.72,
	positionZ = 5.12037,

	directionX = 0,
	directionZ = 0,
	directionY = 0.566434,
	directionW = 0.824107,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc340 = Creature:new {
	objectName = "mosEspaNpc340",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2713.99,
	positionY = 1815.47,
	positionZ = 5.73621,

	directionX = 0,
	directionZ = 0,
	directionY = 0.985889,
	directionW = -0.167402,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc341 = Creature:new {
	objectName = "mosEspaNpc341",
	creatureType = NPC,

	speciesName = "kreetle",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3936955323,
	positionX = -2705.64,
	positionY = 1820.1,
	positionZ = 5.75105,

	directionX = 0,
	directionZ = 0,
	directionY = 0.997151,
	directionW = -0.0754287,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc342 = Creature:new {
	objectName = "mosEspaNpc342",
	creatureType = NPC,

	speciesName = "rockmite",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1647879081,
	positionX = -2714.58,
	positionY = 1828.84,
	positionZ = 5.37967,

	directionX = 0,
	directionZ = 0,
	directionY = 0.841923,
	directionW = -0.539598,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc343 = Creature:new {
	objectName = "mosEspaNpc343",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -2716.18,
	positionY = 1830.71,
	positionZ = 5.32138,

	directionX = 0,
	directionZ = 0,
	directionY = 0.742525,
	directionW = -0.669818,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc344 = Creature:new {
	objectName = "mosEspaNpc344",
	creatureType = NPC,

	speciesName = "worrt",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1368967713,
	positionX = -2613.31,
	positionY = 1969.82,
	positionZ = 5.08118,

	directionX = 0,
	directionZ = 0,
	directionY = -0.108687,
	directionW = 0.994076,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc345 = Creature:new {
	objectName = "mosEspaNpc345",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2621.59,
	positionY = 1967.45,
	positionZ = 5.02486,

	directionX = 0,
	directionZ = 0,
	directionY = -0.124963,
	directionW = 0.992161,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc346 = Creature:new {
	objectName = "mosEspaNpc346",
	creatureType = NPC,

	speciesName = "lesser_desert_womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2613.3,
	positionY = 1956.6,
	positionZ = 5.16549,

	directionX = 0,
	directionZ = 0,
	directionY = 0.994614,
	directionW = -0.103644,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc347 = Creature:new {
	objectName = "mosEspaNpc347",
	creatureType = NPC,

	speciesName = "womprat",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1003281536,
	positionX = -2581.69,
	positionY = 2031.96,
	positionZ = 5.15777,

	directionX = 0,
	directionZ = 0,
	directionY = 0.982819,
	directionW = -0.184573,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc348 = Creature:new {
	objectName = "mosEspaNpc348",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2958892521,
	positionX = -2903.06,
	positionY = 2362.06,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.038965,
	directionW = 0.999241,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc349 = Creature:new {
	objectName = "mosEspaNpc349",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1293171481,
	positionX = -2976.72,
	positionY = 2333.09,
	positionZ = 5.52789,

	directionX = 0,
	directionZ = 0,
	directionY = 0.951451,
	directionW = -0.3078,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc350 = Creature:new {
	objectName = "mosEspaNpc350",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3071423279,
	positionX = -2886.35,
	positionY = 2377.12,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = -0.317377,
	directionW = 0.9483,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc351 = Creature:new {
	objectName = "mosEspaNpc351",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1495617954,
	positionX = -2996.41,
	positionY = 2326.36,
	positionZ = 5.52789,

	directionX = 0,
	directionZ = 0,
	directionY = -2.81304e-08,
	directionW = 1,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc352 = Creature:new {
	objectName = "mosEspaNpc352",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1609219381,
	positionX = -2999.41,
	positionY = 2350.79,
	positionZ = 5.52789,

	directionX = 0,
	directionZ = 0,
	directionY = 0.843485,
	directionW = -0.537153,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc353 = Creature:new {
	objectName = "mosEspaNpc353",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2255262052,
	positionX = -3062.85,
	positionY = 2195.92,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.978412,
	directionW = 0.206664,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc354 = Creature:new {
	objectName = "mosEspaNpc354",
	creatureType = NPC,

	speciesName = "da_la_socuna",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_spawner_n",
	objectCRC = 2236790901,
	positionX = -29.7168,
	positionY = 7.77728,
	positionZ = -0.519991,

	directionX = -1.66112e-08,
	directionZ = 3.87349e-08,
	directionY = 0.459782,
	directionW = 0.888032,
	randomMovement = 0,
	mood = "neutral",
	cellID = 1256068
}

mosEspaNpc355 = Creature:new {
	objectName = "mosEspaNpc355",
	creatureType = NPC,

	speciesName = "gambler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2285654257,
	positionX = -20.6545,
	positionY = 25.0112,
	positionZ = -0.894989,

	directionX = 8.94114e-08,
	directionZ = 2.95035e-07,
	directionY = 3.81441e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256067
}

mosEspaNpc356 = Creature:new {
	objectName = "mosEspaNpc356",
	creatureType = NPC,

	speciesName = "dim_u_preacher",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2984675979,
	positionX = -20.6545,
	positionY = 26.0112,
	positionZ = -0.894989,

	directionX = -1.32163e-07,
	directionZ = 5.92423e-12,
	directionY = 1,
	directionW = -4.48254e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256067
}

mosEspaNpc357 = Creature:new {
	objectName = "mosEspaNpc357",
	creatureType = NPC,

	speciesName = "tatooine_militiaman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1189502506,
	positionX = 2.1656,
	positionY = -15.9672,
	positionZ = -0.894992,

	directionX = 5.96094e-08,
	directionZ = -1.33466e-08,
	directionY = -2.80162e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256061
}

mosEspaNpc358 = Creature:new {
	objectName = "mosEspaNpc358",
	creatureType = NPC,

	speciesName = "gambler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3494490373,
	positionX = 2.1656,
	positionY = -14.9672,
	positionZ = -0.894992,

	directionX = 1.07484e-08,
	directionZ = -5.96086e-08,
	directionY = 1,
	directionW = 4.12495e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256061
}

mosEspaNpc359 = Creature:new {
	objectName = "mosEspaNpc359",
	creatureType = NPC,

	speciesName = "bartender",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3043344299,
	positionX = -11.1703,
	positionY = 1.53149,
	positionZ = -0.894992,

	directionX = 0,
	directionZ = 0,
	directionY = 0.287585,
	directionW = 0.957755,
	randomMovement = 0,
	mood = "neutral",
	cellID = 1256058
}

mosEspaNpc360 = Creature:new {
	objectName = "mosEspaNpc360",
	creatureType = NPC,

	speciesName = "twilek_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3462393809,
	positionX = 10.5758,
	positionY = -3.56401,
	positionZ = -0.894992,

	directionX = 3.40319e-08,
	directionZ = 3.89464e-08,
	directionY = 0.875913,
	directionW = -0.482469,
	randomMovement = 0,
	mood = "",
	cellID = 1256058
}

mosEspaNpc361 = Creature:new {
	objectName = "mosEspaNpc361",
	creatureType = NPC,

	speciesName = "squatter",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3504184450,
	positionX = 12.1732,
	positionY = 2.93609,
	positionZ = -0.894992,

	directionX = -5.96034e-08,
	directionZ = 7.74528e-08,
	directionY = -1.049e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256058
}

mosEspaNpc362 = Creature:new {
	objectName = "mosEspaNpc362",
	creatureType = NPC,

	speciesName = "medic",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3044338694,
	positionX = 12.1732,
	positionY = 3.93609,
	positionZ = -0.894991,

	directionX = -5.08094e-09,
	directionZ = 2.98007e-08,
	directionY = 1,
	directionW = 2.33638e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1256058
}

mosEspaNpc363 = Creature:new {
	objectName = "mosEspaNpc363",
	creatureType = NPC,

	speciesName = "commoner_human_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1359545142,
	positionX = -6.00754,
	positionY = -5.35219,
	positionZ = -0.894992,

	directionX = 1.09453e-07,
	directionZ = -9.67114e-08,
	directionY = 0.902355,
	directionW = -0.430993,
	randomMovement = 0,
	mood = "calm",
	cellID = 1256058
}

mosEspaNpc364 = Creature:new {
	objectName = "mosEspaNpc364",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1359545142,
	positionX = -3046.72,
	positionY = 2133.45,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.820371,
	directionW = -0.571831,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc365 = Creature:new {
	objectName = "mosEspaNpc365",
	creatureType = NPC,

	speciesName = "thug",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2558798248,
	positionX = -3065.25,
	positionY = 2142.42,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.977139,
	directionW = 0.2126,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc366 = Creature:new {
	objectName = "mosEspaNpc366",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1293171481,
	positionX = -24,
	positionY = -4,
	positionZ = 1.6,

	directionX = 0,
	directionZ = 0,
	directionY = 0.402978,
	directionW = 0.915209,
	randomMovement = 0,
	mood = "calm",
	cellID = 1261023
}

mosEspaNpc367 = Creature:new {
	objectName = "mosEspaNpc367",
	creatureType = NPC,

	speciesName = "technician",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 111428352,
	positionX = 7.41432,
	positionY = -6.90893,
	positionZ = 1.00001,

	directionX = -3.79299e-07,
	directionZ = 1.74966e-11,
	directionY = 4.61288e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261017
}

mosEspaNpc368 = Creature:new {
	objectName = "mosEspaNpc368",
	creatureType = NPC,

	speciesName = "tatooine_militiaman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 300124372,
	positionX = 7.41432,
	positionY = -5.80893,
	positionZ = 1.00001,

	directionX = 1.19554e-11,
	directionZ = -4.87697e-07,
	directionY = 1,
	directionW = 2.45139e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261017
}

mosEspaNpc369 = Creature:new {
	objectName = "mosEspaNpc369",
	creatureType = NPC,

	speciesName = "technician",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 111428352,
	positionX = 20.2715,
	positionY = -1.14578,
	positionZ = 1.28309,

	directionX = -1.08361e-07,
	directionZ = -2.7289e-12,
	directionY = -2.51833e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261018
}

mosEspaNpc370 = Creature:new {
	objectName = "mosEspaNpc370",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3499278053,
	positionX = 20.2715,
	positionY = -0.0457823,
	positionZ = 1.28309,

	directionX = -6.48271e-12,
	directionZ = 1.0838e-07,
	directionY = 1,
	directionW = 5.98144e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261018
}

mosEspaNpc371 = Creature:new {
	objectName = "mosEspaNpc371",
	creatureType = NPC,

	speciesName = "rodian_clan_medic",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1938688799,
	positionX = 19.1715,
	positionY = -0.0457823,
	positionZ = 1.28309,

	directionX = -2.93281e-08,
	directionZ = 7.07945e-08,
	directionY = 0.923861,
	directionW = 0.382729,
	randomMovement = 0,
	mood = "conversation",
	cellID = 1261018
}

mosEspaNpc372 = Creature:new {
	objectName = "mosEspaNpc372",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2456484453,
	positionX = 20.2668,
	positionY = 15.1105,
	positionZ = 1.56616,

	directionX = 0,
	directionZ = 0,
	directionY = 0.857263,
	directionW = -0.514878,
	randomMovement = 0,
	mood = "calm",
	cellID = 1261018
}

mosEspaNpc373 = Creature:new {
	objectName = "mosEspaNpc373",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1970430892,
	positionX = -3055.28,
	positionY = 2098.76,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.878124,
	directionW = -0.478434,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc374 = Creature:new {
	objectName = "mosEspaNpc374",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3605251727,
	positionX = -3019.69,
	positionY = 2114.97,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.598094,
	directionW = 0.801426,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc375 = Creature:new {
	objectName = "mosEspaNpc375",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3550979552,
	positionX = -2914.38,
	positionY = 1984.92,
	positionZ = 5,

	directionX = 0,
	directionZ = 0,
	directionY = 0.230515,
	directionW = 0.973069,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc376 = Creature:new {
	objectName = "mosEspaNpc376",
	creatureType = NPC,

	speciesName = "r4",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3969267025,
	positionX = -2871.38,
	positionY = 1985.32,
	positionZ = 6.12074,

	directionX = 0,
	directionZ = 0,
	directionY = 0.806519,
	directionW = -0.591208,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

mosEspaNpc377 = Creature:new {
	objectName = "mosEspaNpc377",
	creatureType = NPC,

	speciesName = "crafting_contractor",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2495515674,
	positionX = -3.69,
	positionY = -6,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = -0,
	directionY = 0.0958457,
	directionW = 0.995396,
	randomMovement = 0,
	mood = "calm",
	cellID = 1256306
}

mosEspaNpc378 = Creature:new {
	objectName = "mosEspaNpc378",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3494490373,
	positionX = 3.29,
	positionY = -9.58,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.824126,
	directionW = -0.566406,
	randomMovement = 0,
	mood = "calm",
	cellID = 1256011
}

mosEspaNpc379 = Creature:new {
	objectName = "mosEspaNpc379",
	creatureType = NPC,

	speciesName = "coa3_information_rebel",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3881299181,
	positionX = 14.2091,
	positionY = -10.1408,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.975088,
	directionW = -0.221819,
	randomMovement = 0,
	mood = "calm",
	cellID = 1256010
}

