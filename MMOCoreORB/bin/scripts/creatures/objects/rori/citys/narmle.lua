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

narmleNpc1 = Creature:new {
	objectName = "narmleNpc1",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 117165421,
	positionX = -5443.54,
	positionY = -2174.68,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.779773,
	directionW = -0.626063,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc2 = Creature:new {
	objectName = "narmleNpc2",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3071423279,
	positionX = -5418.39,
	positionY = -2093.5,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.115259,
	directionW = 0.993335,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc3 = Creature:new {
	objectName = "narmleNpc3",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2500249611,
	positionX = -46.8088,
	positionY = 30.7844,
	positionZ = 2.63942,

	directionX = -6.50263e-07,
	directionZ = -3.38128e-11,
	directionY = -5.19987e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635445
}

narmleNpc4 = Creature:new {
	objectName = "narmleNpc4",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1663940433,
	positionX = -46.8088,
	positionY = 31.8844,
	positionZ = 2.63942,

	directionX = -2.10437e-11,
	directionZ = 7.58674e-07,
	directionY = 1,
	directionW = 2.77375e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635445
}

narmleNpc5 = Creature:new {
	objectName = "narmleNpc5",
	creatureType = NPC,

	speciesName = "spice_collective_courier",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4057893577,
	positionX = -47.9088,
	positionY = 31.8844,
	positionZ = 2.63942,

	directionX = -2.05299e-07,
	directionZ = 4.95584e-07,
	directionY = 0.923866,
	directionW = 0.382717,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635445
}

narmleNpc6 = Creature:new {
	objectName = "narmleNpc6",
	creatureType = NPC,

	speciesName = "spacer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2941743775,
	positionX = -34.4809,
	positionY = 60.9461,
	positionZ = 1.63942,

	directionX = 8.12845e-07,
	directionZ = 2.11312e-11,
	directionY = -2.59965e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635442
}

narmleNpc7 = Creature:new {
	objectName = "narmleNpc7",
	creatureType = NPC,

	speciesName = "spacer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2268027596,
	positionX = -34.4809,
	positionY = 62.0461,
	positionZ = 1.63942,

	directionX = -1.97371e-11,
	directionZ = -7.5854e-07,
	directionY = 1,
	directionW = -2.60199e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635442
}

narmleNpc8 = Creature:new {
	objectName = "narmleNpc8",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 616279196,
	positionX = 40.9354,
	positionY = 36.9425,
	positionZ = 0.639417,

	directionX = -1.30035e-06,
	directionZ = -9.24663e-11,
	directionY = -7.11086e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635440
}

narmleNpc9 = Creature:new {
	objectName = "narmleNpc9",
	creatureType = NPC,

	speciesName = "gambler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 197800981,
	positionX = 40.9354,
	positionY = 38.0425,
	positionZ = 0.639417,

	directionX = 9.2504e-11,
	directionZ = 1.30056e-06,
	directionY = 1,
	directionW = -7.11265e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635440
}

narmleNpc10 = Creature:new {
	objectName = "narmleNpc10",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 117506864,
	positionX = -5317.51,
	positionY = -2266.1,
	positionZ = 80.4691,

	directionX = 0.0110368,
	directionZ = -0.00735555,
	directionY = 0.994803,
	directionW = 0.10095,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc11 = Creature:new {
	objectName = "narmleNpc11",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3605251727,
	positionX = -5313.48,
	positionY = -2114.04,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = -0.347728,
	directionW = 0.937596,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc12 = Creature:new {
	objectName = "narmleNpc12",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 706793692,
	positionX = -5325.77,
	positionY = -2068.85,
	positionZ = 80.093,

	directionX = 0,
	directionZ = 0,
	directionY = 0.189661,
	directionW = 0.98185,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc14 = Creature:new {
	objectName = "narmleNpc14",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2316353705,
	positionX = -5298.83,
	positionY = -2198.9,
	positionZ = 80.0772,

	directionX = 0,
	directionZ = 0,
	directionY = 0.221127,
	directionW = 0.975245,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc15 = Creature:new {
	objectName = "narmleNpc15",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 288221603,
	positionX = -5259.69,
	positionY = -2239.88,
	positionZ = 80.0145,

	directionX = 0,
	directionZ = 0,
	directionY = -0.262592,
	directionW = 0.964907,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc16 = Creature:new {
	objectName = "narmleNpc16",
	creatureType = NPC,

	speciesName = "itp_thrawn_winthazen",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -5299,
	positionY = -2098.49,
	positionZ = 80.0686,

	directionX = 0,
	directionZ = 0,
	directionY = 0.993431,
	directionW = -0.114434,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

narmleNpc17 = Creature:new {
	objectName = "narmleNpc17",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -5312.76,
	positionY = -2219.53,
	positionZ = 80.102,

	directionX = 0,
	directionZ = 0,
	directionY = -0.405222,
	directionW = 0.914219,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc19 = Creature:new {
	objectName = "narmleNpc19",
	creatureType = NPC,

	speciesName = "coa2_imperial_coordinator",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3423844128,
	positionX = -5257.05,
	positionY = -2254.85,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.375456,
	directionW = 0.92684,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 0
}

narmleNpc20 = Creature:new {
	objectName = "narmleNpc20",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3929274561,
	positionX = -5231.19,
	positionY = -2208.19,
	positionZ = 80.067,

	directionX = 0,
	directionZ = 0,
	directionY = -0.129922,
	directionW = 0.991524,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc21 = Creature:new {
	objectName = "narmleNpc21",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 36713428,
	positionX = -5230.23,
	positionY = -2182.25,
	positionZ = 80.3685,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0478879,
	directionW = 0.998853,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc23 = Creature:new {
	objectName = "narmleNpc23",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -5209.77,
	positionY = -2207.36,
	positionZ = 80.0124,

	directionX = 0,
	directionZ = 0,
	directionY = 0.925163,
	directionW = 0.379571,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc24 = Creature:new {
	objectName = "narmleNpc24",
	creatureType = NPC,

	speciesName = "r5",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2778419932,
	positionX = -5208.93,
	positionY = -2249.14,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0285716,
	directionW = 0.999592,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc25 = Creature:new {
	objectName = "narmleNpc25",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3112126536,
	positionX = -5210.74,
	positionY = -2269.67,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.907323,
	directionW = 0.420435,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc26 = Creature:new {
	objectName = "narmleNpc26",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1117545308,
	positionX = -5268.57,
	positionY = -2335.87,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.418449,
	directionW = 0.90824,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc45 = Creature:new {
	objectName = "narmleNpc45",
	creatureType = NPC,

	speciesName = "surgical_droid_21b",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3419245135,
	positionX = -25.52,
	positionY = -3.48,
	positionZ = 0.26,

	directionX = 0,
	directionZ = 0,
	directionY = 0.576679,
	directionW = 0.816971,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635424
}

narmleNpc47 = Creature:new {
	objectName = "narmleNpc47",
	creatureType = NPC,

	speciesName = "fringer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1660701062,
	positionX = -33.7407,
	positionY = -13.9897,
	positionZ = 0.259965,

	directionX = 0,
	directionZ = 0.00106742,
	directionY = 0.999999,
	directionW = 0,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc48 = Creature:new {
	objectName = "narmleNpc48",
	creatureType = NPC,

	speciesName = "zabrak_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 371119389,
	positionX = -33.7407,
	positionY = -13.9927,
	positionZ = 0.259972,

	directionX = 0.00144544,
	directionZ = 0,
	directionY = 0,
	directionW = 0.999999,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc49 = Creature:new {
	objectName = "narmleNpc49",
	creatureType = NPC,

	speciesName = "bothan_information_broker",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3885288051,
	positionX = -33.7407,
	positionY = -13.9897,
	positionZ = 0.259965,

	directionX = 0,
	directionZ = -0.306582,
	directionY = 0.951844,
	directionW = 0,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc50 = Creature:new {
	objectName = "narmleNpc50",
	creatureType = NPC,

	speciesName = "medic",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1153411498,
	positionX = -33.7407,
	positionY = -13.9927,
	positionZ = 0.259972,

	directionX = 0,
	directionZ = -0.204747,
	directionY = 0.978815,
	directionW = 0,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc51 = Creature:new {
	objectName = "narmleNpc51",
	creatureType = NPC,

	speciesName = "explorer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4244927617,
	positionX = -33.7407,
	positionY = -13.9927,
	positionZ = 0.259972,

	directionX = -4.50636e-09,
	directionZ = -0.204747,
	directionY = 0.978815,
	directionW = -2.15431e-08,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc52 = Creature:new {
	objectName = "narmleNpc52",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2516816782,
	positionX = -33.7407,
	positionY = -13.9927,
	positionZ = 0.259972,

	directionX = 1.0374e-08,
	directionZ = -0.204747,
	directionY = 0.978815,
	directionW = 4.95939e-08,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc53 = Creature:new {
	objectName = "narmleNpc53",
	creatureType = NPC,

	speciesName = "mercenary",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2394298047,
	positionX = -33.7407,
	positionY = -13.9897,
	positionZ = 0.259965,

	directionX = 0,
	directionZ = 0.00106742,
	directionY = 0.999999,
	directionW = 0,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635423
}

narmleNpc54 = Creature:new {
	objectName = "narmleNpc54",
	creatureType = NPC,

	speciesName = "itp_thrawn_keeloo",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 208413022,
	positionX = -5130.31,
	positionY = -2270,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.962753,
	directionW = 0.270383,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc55 = Creature:new {
	objectName = "narmleNpc55",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 41146771,
	positionX = -5089.55,
	positionY = -2268.5,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = -0.490541,
	directionW = 0.871418,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc56 = Creature:new {
	objectName = "narmleNpc56",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 41146771,
	positionX = -5033.6,
	positionY = -2224.65,
	positionZ = 80.0574,

	directionX = 0,
	directionZ = 0,
	directionY = 0.889882,
	directionW = -0.456192,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc58 = Creature:new {
	objectName = "narmleNpc58",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3126739438,
	positionX = -5010.3,
	positionY = -2228.89,
	positionZ = 80.2656,

	directionX = 0,
	directionZ = 0,
	directionY = 0.881529,
	directionW = -0.47213,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc59 = Creature:new {
	objectName = "narmleNpc59",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 45306224,
	positionX = -5088.04,
	positionY = -2296.7,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = -0.543146,
	directionW = 0.839638,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc61 = Creature:new {
	objectName = "narmleNpc61",
	creatureType = NPC,

	speciesName = "protocol_droid_3po",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3229997144,
	positionX = -4975,
	positionY = -2227,
	positionZ = 79.8943,

	directionX = 0.0058587,
	directionZ = -0.00128499,
	directionY = 0.214234,
	directionW = 0.976764,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc62 = Creature:new {
	objectName = "narmleNpc62",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 138244543,
	positionX = -4983.01,
	positionY = -2297.39,
	positionZ = 79.9956,

	directionX = 0,
	directionZ = 0,
	directionY = 0.976613,
	directionW = -0.215005,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc63 = Creature:new {
	objectName = "narmleNpc63",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 824463446,
	positionX = -4966.21,
	positionY = -2321.09,
	positionZ = 79.9706,

	directionX = 0,
	directionZ = 0,
	directionY = 0.916767,
	directionW = 0.399422,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc69 = Creature:new {
	objectName = "narmleNpc69",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4103475195,
	positionX = -4984.34,
	positionY = -2335.05,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0725806,
	directionW = 0.997363,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc70 = Creature:new {
	objectName = "narmleNpc70",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1527998977,
	positionX = -4873.48,
	positionY = -2256.69,
	positionZ = 82.0523,

	directionX = 0,
	directionZ = 0,
	directionY = 0.792295,
	directionW = 0.610139,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc71 = Creature:new {
	objectName = "narmleNpc71",
	creatureType = NPC,

	speciesName = "rodian_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3021148797,
	positionX = -4877.1,
	positionY = -2251.47,
	positionZ = 81.0647,

	directionX = 0,
	directionZ = 0,
	directionY = 0.968951,
	directionW = -0.247252,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc72 = Creature:new {
	objectName = "narmleNpc72",
	creatureType = NPC,

	speciesName = "rodian_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 2295771949,
	positionX = -4864.56,
	positionY = -2247.82,
	positionZ = 80.8399,

	directionX = 0,
	directionZ = 0,
	directionY = 0.227357,
	directionW = 0.973812,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc73 = Creature:new {
	objectName = "narmleNpc73",
	creatureType = NPC,

	speciesName = "rodian_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3021148797,
	positionX = -4883.47,
	positionY = -2246.39,
	positionZ = 81.097,

	directionX = 0,
	directionZ = 0,
	directionY = 0.950042,
	directionW = -0.312122,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc74 = Creature:new {
	objectName = "narmleNpc74",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 801261173,
	positionX = -4864.19,
	positionY = -2246.87,
	positionZ = 80.5081,

	directionX = 0,
	directionZ = 0,
	directionY = 0.865345,
	directionW = -0.501176,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc75 = Creature:new {
	objectName = "narmleNpc75",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 683714709,
	positionX = -4863.33,
	positionY = -2253.58,
	positionZ = 80.5281,

	directionX = 0,
	directionZ = 0,
	directionY = 0.989053,
	directionW = -0.147562,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc76 = Creature:new {
	objectName = "narmleNpc76",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1527998977,
	positionX = -4872.13,
	positionY = -2244.19,
	positionZ = 79.6112,

	directionX = 0,
	directionZ = 0,
	directionY = 0.958097,
	directionW = -0.286443,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc83 = Creature:new {
	objectName = "narmleNpc83",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 41146771,
	positionX = -4967.75,
	positionY = -2379.52,
	positionZ = 79.9998,

	directionX = 0,
	directionZ = 0,
	directionY = 0.938318,
	directionW = 0.345773,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc86 = Creature:new {
	objectName = "narmleNpc86",
	creatureType = NPC,

	speciesName = "smuggler_patrol_thief_7",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1077493527,
	positionX = -4866.9,
	positionY = -2301.82,
	positionZ = 77.8474,

	directionX = 0,
	directionZ = 0,
	directionY = -0.422881,
	directionW = 0.906185,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc87 = Creature:new {
	objectName = "narmleNpc87",
	creatureType = NPC,

	speciesName = "smuggler_patrol_thief_7",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2556640383,
	positionX = -4867.56,
	positionY = -2301.95,
	positionZ = 77.7862,

	directionX = 0,
	directionZ = 0,
	directionY = -0.422892,
	directionW = 0.90618,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc88 = Creature:new {
	objectName = "narmleNpc88",
	creatureType = NPC,

	speciesName = "smuggler_patrol_thief_7",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3984356119,
	positionX = -4833.67,
	positionY = -2310.94,
	positionZ = 79.773,

	directionX = 0,
	directionZ = 0,
	directionY = 0.973736,
	directionW = 0.227682,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc89 = Creature:new {
	objectName = "narmleNpc89",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1599346226,
	positionX = 15.588,
	positionY = 72.3985,
	positionZ = 2.12878,

	directionX = -9.49902e-06,
	directionZ = 1.23181e-05,
	directionY = -0.591812,
	directionW = 0.806076,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635403
}

narmleNpc90 = Creature:new {
	objectName = "narmleNpc90",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2595785783,
	positionX = 19.26,
	positionY = 56.13,
	positionZ = 2.12847,

	directionX = 0,
	directionZ = 0,
	directionY = 0.731354,
	directionW = -0.681998,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635403
}

narmleNpc91 = Creature:new {
	objectName = "narmleNpc91",
	creatureType = NPC,

	speciesName = "quest_crowd_pleaser_theater_manager",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3733923381,
	positionX = 21.99,
	positionY = 64.05,
	positionZ = 2.12804,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0348995,
	directionW = 0.999391,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635403
}

narmleNpc92 = Creature:new {
	objectName = "narmleNpc92",
	creatureType = NPC,

	speciesName = "noble",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 951465831,
	positionX = 28.93,
	positionY = 58.19,
	positionZ = 2.12878,

	directionX = 0,
	directionZ = 0,
	directionY = 0.93358,
	directionW = -0.358368,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635402
}

narmleNpc93 = Creature:new {
	objectName = "narmleNpc93",
	creatureType = NPC,

	speciesName = "itp_vader_rebel_courier",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1678608918,
	positionX = -4968,
	positionY = -2399,
	positionZ = 79.9912,

	directionX = 0,
	directionZ = 0,
	directionY = 0.934135,
	directionW = -0.35692,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc94 = Creature:new {
	objectName = "narmleNpc94",
	creatureType = NPC,

	speciesName = "smuggler_patrol_thief_7",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2121620877,
	positionX = -4822.52,
	positionY = -2301.21,
	positionZ = 79.1924,

	directionX = 0,
	directionZ = 0,
	directionY = 0.605139,
	directionW = 0.79612,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc95 = Creature:new {
	objectName = "narmleNpc95",
	creatureType = NPC,

	speciesName = "smuggler_patrol_thief_7",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2753395803,
	positionX = -4822.33,
	positionY = -2248.25,
	positionZ = 77.9171,

	directionX = 0,
	directionZ = 0,
	directionY = 0.983964,
	directionW = -0.178365,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc99 = Creature:new {
	objectName = "narmleNpc99",
	creatureType = NPC,

	speciesName = "r3",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 393551429,
	positionX = -5065.29,
	positionY = -2334.08,
	positionZ = 80,

	directionX = 0,
	directionZ = -0,
	directionY = 0.712181,
	directionW = 0.701996,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc100 = Creature:new {
	objectName = "narmleNpc100",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3630353613,
	positionX = -5036.13,
	positionY = -2402.18,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.943432,
	directionW = 0.331566,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc106 = Creature:new {
	objectName = "narmleNpc106",
	creatureType = NPC,

	speciesName = "cll8_binary_load_lifter",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 103360686,
	positionX = -5088.79,
	positionY = -2444.55,
	positionZ = 80.0022,

	directionX = 0,
	directionZ = 0,
	directionY = 0.0320998,
	directionW = 0.999485,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc113 = Creature:new {
	objectName = "narmleNpc113",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3106175116,
	positionX = -5120.56,
	positionY = -2443.12,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.161872,
	directionW = 0.986812,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc114 = Creature:new {
	objectName = "narmleNpc114",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3498486854,
	positionX = -5160.16,
	positionY = -2499.29,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.885025,
	directionW = -0.465544,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc115 = Creature:new {
	objectName = "narmleNpc115",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1794132300,
	positionX = -5189.88,
	positionY = -2501.35,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.213605,
	directionW = 0.97692,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc116 = Creature:new {
	objectName = "narmleNpc116",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 181687135,
	positionX = -5190.22,
	positionY = -2461.09,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.839051,
	directionW = 0.544053,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc117 = Creature:new {
	objectName = "narmleNpc117",
	creatureType = NPC,

	speciesName = "rodian_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3021148797,
	positionX = -5131.61,
	positionY = -2660.4,
	positionZ = 76.1337,

	directionX = 0,
	directionZ = 0,
	directionY = 0.330335,
	directionW = 0.943864,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc118 = Creature:new {
	objectName = "narmleNpc118",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1527998977,
	positionX = -5142.7,
	positionY = -2664.06,
	positionZ = 76.6997,

	directionX = 0,
	directionZ = 0,
	directionY = -0.302616,
	directionW = 0.953113,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc120 = Creature:new {
	objectName = "narmleNpc120",
	creatureType = NPC,

	speciesName = "rodian_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 2295771949,
	positionX = -5137.61,
	positionY = -2671.86,
	positionZ = 76.8892,

	directionX = 0,
	directionZ = -0,
	directionY = -0.535623,
	directionW = 0.844457,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc121 = Creature:new {
	objectName = "narmleNpc121",
	creatureType = NPC,

	speciesName = "bith_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 915891720,
	positionX = -5130.94,
	positionY = -2669.41,
	positionZ = 76.5926,

	directionX = 0,
	directionZ = 0,
	directionY = -0.422138,
	directionW = 0.906532,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc124 = Creature:new {
	objectName = "narmleNpc124",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4244927617,
	positionX = -5235.04,
	positionY = -2430.93,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = -0.34884,
	directionW = 0.937182,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc125 = Creature:new {
	objectName = "narmleNpc125",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 4130887746,
	positionX = -5246.95,
	positionY = -2387.01,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = -0.476536,
	directionW = 0.879155,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc126 = Creature:new {
	objectName = "narmleNpc126",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2516816782,
	positionX = -5235.88,
	positionY = -2387.38,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.931716,
	directionW = 0.363187,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc131 = Creature:new {
	objectName = "narmleNpc131",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3494490373,
	positionX = -5238.69,
	positionY = -2355.76,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.492312,
	directionW = 0.870419,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc132 = Creature:new {
	objectName = "narmleNpc132",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1678608918,
	positionX = -5323.84,
	positionY = -2307.54,
	positionZ = 80.1242,

	directionX = 0,
	directionZ = 0,
	directionY = -0.440874,
	directionW = 0.897569,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc133 = Creature:new {
	objectName = "narmleNpc133",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 1352060508,
	positionX = -23.809,
	positionY = -11.9706,
	positionZ = 1.6,

	directionX = 1.53165e-07,
	directionZ = -6.40766e-08,
	directionY = 0.385937,
	directionW = 0.922525,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635599
}

narmleNpc134 = Creature:new {
	objectName = "narmleNpc134",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3349491438,
	positionX = -24,
	positionY = -4,
	positionZ = 1.6,

	directionX = 0,
	directionZ = 0,
	directionY = -0.697278,
	directionW = 0.716801,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635599
}

narmleNpc135 = Creature:new {
	objectName = "narmleNpc135",
	creatureType = NPC,

	speciesName = "clone_relics_kole",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3181883060,
	positionX = -23.3,
	positionY = -17.6,
	positionZ = 1.6,

	directionX = 0,
	directionZ = -0,
	directionY = 0.5373,
	directionW = 0.843391,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635599
}

narmleNpc136 = Creature:new {
	objectName = "narmleNpc136",
	creatureType = NPC,

	speciesName = "scientist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3044338694,
	positionX = 26.0684,
	positionY = -0.818005,
	positionZ = 1.28309,

	directionX = 1.13792e-06,
	directionZ = 7.92048e-12,
	directionY = -6.96048e-06,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635594
}

narmleNpc137 = Creature:new {
	objectName = "narmleNpc137",
	creatureType = NPC,

	speciesName = "technician",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3004861826,
	positionX = 26.0684,
	positionY = 0.281995,
	positionZ = 1.28309,

	directionX = -7.88034e-12,
	directionZ = -1.13779e-06,
	directionY = 1,
	directionW = -6.92599e-06,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635594
}

narmleNpc138 = Creature:new {
	objectName = "narmleNpc138",
	creatureType = NPC,

	speciesName = "explorer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1812306872,
	positionX = 24.9684,
	positionY = 0.281995,
	positionZ = 1.28309,

	directionX = 3.07881e-07,
	directionZ = -7.4335e-07,
	directionY = 0.92389,
	directionW = 0.382657,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635594
}

narmleNpc139 = Creature:new {
	objectName = "narmleNpc139",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1395390566,
	positionX = 4.86047,
	positionY = 5.92573,
	positionZ = 0.999988,

	directionX = -1.89668e-06,
	directionZ = -9.81949e-11,
	directionY = -5.1772e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635593
}

narmleNpc140 = Creature:new {
	objectName = "narmleNpc140",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1270757117,
	positionX = 4.86047,
	positionY = 7.02573,
	positionZ = 0.999992,

	directionX = -1.72767e-10,
	directionZ = -3.33259e-06,
	directionY = 1,
	directionW = -5.18416e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635593
}

narmleNpc141 = Creature:new {
	objectName = "narmleNpc141",
	creatureType = NPC,

	speciesName = "spacer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2941743775,
	positionX = -13.3747,
	positionY = -3.41628,
	positionZ = 1.00011,

	directionX = -0.000118764,
	directionZ = 1.12197e-08,
	directionY = 9.44705e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635595
}

narmleNpc142 = Creature:new {
	objectName = "narmleNpc142",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2497774199,
	positionX = -13.3747,
	positionY = -2.31628,
	positionZ = 1.00037,

	directionX = 1.1024e-08,
	directionZ = -0.000116664,
	directionY = 1,
	directionW = 9.44936e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635595
}

narmleNpc143 = Creature:new {
	objectName = "narmleNpc143",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 53895320,
	positionX = -5431.64,
	positionY = -2242.36,
	positionZ = 79.9998,

	directionX = 0,
	directionZ = 0,
	directionY = 0.60663,
	directionW = 0.794985,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc145 = Creature:new {
	objectName = "narmleNpc145",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2027163053,
	positionX = -5479.26,
	positionY = -2117.4,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.990804,
	directionW = -0.135302,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc155 = Creature:new {
	objectName = "narmleNpc155",
	creatureType = NPC,

	speciesName = "eg6_power_droid",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 504745581,
	positionX = -5187.37,
	positionY = -2283.09,
	positionZ = 80,

	directionX = -0,
	directionZ = 0,
	directionY = -0.649571,
	directionW = 0.760301,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc157 = Creature:new {
	objectName = "narmleNpc157",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2958892521,
	positionX = -5096.5,
	positionY = -2317.99,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.903459,
	directionW = 0.428674,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc162 = Creature:new {
	objectName = "narmleNpc162",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2831733618,
	positionX = -5137.08,
	positionY = -2408.5,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.970994,
	directionW = 0.239102,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc163 = Creature:new {
	objectName = "narmleNpc163",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 438738923,
	positionX = -5088.2,
	positionY = -2407.66,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.934112,
	directionW = 0.356979,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}

narmleNpc164 = Creature:new {
	objectName = "narmleNpc164",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2497774199,
	positionX = 3.29,
	positionY = -9.58,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.824126,
	directionW = -0.566406,
	randomMovement = 0,
	mood = "calm",
	cellID = 4615384
}

narmleNpc165 = Creature:new {
	objectName = "narmleNpc165",
	creatureType = NPC,

	speciesName = "coa3_information_imperial",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2887599713,
	positionX = 14.307,
	positionY = -8.87086,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.803685,
	directionW = -0.595055,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 4615383
}

narmleNpc166 = Creature:new {
	objectName = "narmleNpc166",
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
	directionZ = 0,
	directionY = 0.0958458,
	directionW = 0.995396,
	randomMovement = 0,
	mood = "calm",
	cellID = 4615380
}

narmleNpc167 = Creature:new {
	objectName = "narmleNpc167",
	creatureType = NPC,

	speciesName = "hunter",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2594882157,
	positionX = -14.01,
	positionY = -8.53,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.866025,
	directionW = 0.5,
	randomMovement = 0,
	mood = "calm",
	cellID = 4615375
}

narmleNpc168 = Creature:new {
	objectName = "narmleNpc168",
	creatureType = NPC,

	speciesName = "businessman",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1341565664,
	positionX = 3.32,
	positionY = -8.49,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.913545,
	directionW = -0.406737,
	randomMovement = 0,
	mood = "calm",
	cellID = 4615374
}

narmleNpc169 = Creature:new {
	objectName = "narmleNpc169",
	creatureType = NPC,

	speciesName = "coa3_tactical_imperial",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3843039724,
	positionX = 9.68564,
	positionY = 0.462498,
	positionZ = 1.13306,

	directionX = 0,
	directionZ = 0,
	directionY = 0.932033,
	directionW = -0.362373,
	randomMovement = 0,
	mood = "npc_imperial",
	cellID = 4615371
}

narmleNpc170 = Creature:new {
	objectName = "narmleNpc170",
	creatureType = NPC,

	speciesName = "spacer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3456571922,
	positionX = -1.64601,
	positionY = -17.4847,
	positionZ = -9,

	directionX = 0,
	directionZ = 0,
	directionY = -6.79871e-06,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635529
}

narmleNpc171 = Creature:new {
	objectName = "narmleNpc171",
	creatureType = NPC,

	speciesName = "farmer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 288221603,
	positionX = -1.64601,
	positionY = -16.3847,
	positionZ = -9,

	directionX = 0,
	directionZ = 0,
	directionY = 1,
	directionW = -7.67033e-06,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635529
}

narmleNpc172 = Creature:new {
	objectName = "narmleNpc172",
	creatureType = NPC,

	speciesName = "smuggler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3456571922,
	positionX = -2.74601,
	positionY = -16.3847,
	positionZ = -9,

	directionX = 0,
	directionZ = 0,
	directionY = 0.923894,
	directionW = 0.382649,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635529
}

narmleNpc173 = Creature:new {
	objectName = "narmleNpc173",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3542800680,
	positionX = 3.05378,
	positionY = -3.38406,
	positionZ = -9,

	directionX = 0,
	directionZ = 0,
	directionY = -3.52803e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635528
}

narmleNpc174 = Creature:new {
	objectName = "narmleNpc174",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1117545308,
	positionX = 3.05378,
	positionY = -2.28406,
	positionZ = -9,

	directionX = 0,
	directionZ = 0,
	directionY = 1,
	directionW = -3.62157e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635528
}

narmleNpc175 = Creature:new {
	objectName = "narmleNpc175",
	creatureType = NPC,

	speciesName = "human_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3023398566,
	positionX = -10.8894,
	positionY = -21.0555,
	positionZ = 1.75,

	directionX = 0,
	directionZ = 0,
	directionY = 0.839566,
	directionW = -0.543257,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635527
}

narmleNpc176 = Creature:new {
	objectName = "narmleNpc176",
	creatureType = NPC,

	speciesName = "bith_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 4012550111,
	positionX = 11.5718,
	positionY = -20.3291,
	positionZ = 1.75,

	directionX = -1.0836e-07,
	directionZ = -3.56897e-12,
	directionY = -3.29361e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635527
}

narmleNpc177 = Creature:new {
	objectName = "narmleNpc177",
	creatureType = NPC,

	speciesName = "entertainer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 795770506,
	positionX = 11.5718,
	positionY = -19.2291,
	positionZ = 1.75,

	directionX = 3.664e-12,
	directionZ = 1.08374e-07,
	directionY = 1,
	directionW = -3.38088e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635527
}

narmleNpc178 = Creature:new {
	objectName = "narmleNpc178",
	creatureType = NPC,

	speciesName = "farmer_agriculturalist",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1794187804,
	positionX = 3.50051,
	positionY = 6.16449,
	positionZ = 2.25,

	directionX = 0,
	directionZ = 0,
	directionY = -4.5616e-06,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc179 = Creature:new {
	objectName = "narmleNpc179",
	creatureType = NPC,

	speciesName = "mercenary",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2394298047,
	positionX = 3.50051,
	positionY = 6.74,
	positionZ = 2.25,

	directionX = 0,
	directionZ = 0,
	directionY = 1,
	directionW = -6.00684e-06,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc180 = Creature:new {
	objectName = "narmleNpc180",
	creatureType = NPC,

	speciesName = "miner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 4029226753,
	positionX = -9.28285,
	positionY = -5.60831,
	positionZ = 1.75,

	directionX = -1.08369e-07,
	directionZ = -5.73561e-12,
	directionY = -5.29265e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc181 = Creature:new {
	objectName = "narmleNpc181",
	creatureType = NPC,

	speciesName = "bodyguard",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 1681935872,
	positionX = -9.28285,
	positionY = -4.50831,
	positionZ = 1.75,

	directionX = 5.82472e-12,
	directionZ = 1.08365e-07,
	directionY = 1,
	directionW = -5.37508e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc182 = Creature:new {
	objectName = "narmleNpc182",
	creatureType = NPC,

	speciesName = "explorer",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3889120700,
	positionX = 5.64659,
	positionY = -9.1775,
	positionZ = 1.1544,

	directionX = 3.25158e-07,
	directionZ = 1.80417e-11,
	directionY = -5.54858e-05,
	directionW = 1,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc183 = Creature:new {
	objectName = "narmleNpc183",
	creatureType = NPC,

	speciesName = "smuggler",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 3456571922,
	positionX = 5.64659,
	positionY = -8.0775,
	positionZ = 1.1544,

	directionX = 1.76795e-11,
	directionZ = -3.25045e-07,
	directionY = 1,
	directionW = 5.43908e-05,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc184 = Creature:new {
	objectName = "narmleNpc184",
	creatureType = NPC,

	speciesName = "rodian_base_female",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 3848964537,
	positionX = 4.54659,
	positionY = -8.0775,
	positionZ = 1.1544,

	directionX = 8.79556e-08,
	directionZ = -2.1236e-07,
	directionY = 0.92389,
	directionW = 0.382658,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc185 = Creature:new {
	objectName = "narmleNpc185",
	creatureType = NPC,

	speciesName = "devaronian_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 497085163,
	positionX = 4.54659,
	positionY = -9.1775,
	positionZ = 1.1544,

	directionX = 2.12418e-07,
	directionZ = -8.79874e-08,
	directionY = 0.382688,
	directionW = 0.923878,
	randomMovement = 0,
	mood = "conversation",
	cellID = 4635526
}

narmleNpc186 = Creature:new {
	objectName = "narmleNpc186",
	creatureType = NPC,

	speciesName = "human_base_male",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "npc_name",
	objectCRC = 2754521442,
	positionX = -17.9957,
	positionY = 17.3679,
	positionZ = 2.25,

	directionX = 0,
	directionZ = 0,
	directionY = 0.395651,
	directionW = 0.918401,
	randomMovement = 0,
	mood = "calm",
	cellID = 4635522
}

narmleNpc187 = Creature:new {
	objectName = "narmleNpc187",
	creatureType = NPC,

	speciesName = "commoner",
	combatFlags = 0,
	creatureBitmask = 264,
	stfName = "mob/creature_names",
	objectCRC = 2433966680,
	positionX = -5160.44,
	positionY = -2382.87,
	positionZ = 80,

	directionX = 0,
	directionZ = 0,
	directionY = 0.82583,
	directionW = -0.563919,
	randomMovement = 0,
	mood = "calm",
	cellID = 0
}
