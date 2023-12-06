--[[ Added Tests
	http://pets.furrycat.net/

	"FurryCat Test - ju6d14qq", "dna_set:ju6d14qq",
	"FurryCat Test - d5j7caq6", "dna_set:d5j7caq6",
	"FurryCat Test - ke5nbvgo", "dna_set:ke5nbvgo",
	"FurryCat Test - dcfolokr", "dna_set:dcfolokr",
	"FurryCat Test - jgbq7aiq", "dna_set:jgbq7aiq",
	"FurryCat Test - o97m0aan", "dna_set:o97m0aan",
	"FurryCat Test - mmhkbp03", "dna_set:mmhkbp03",

	1,"object/tangible/component/dna/dna_sample_very_high.iff")
	2,"object/tangible/component/dna/dna_sample_high.iff")
	3,"object/tangible/component/dna/dna_sample_above_average.iff")
	4,"object/tangible/component/dna/dna_sample_average.iff")
	5,"object/tangible/component/dna/dna_sample_below_average.iff")
	6,"object/tangible/component/dna/dna_sample_low.iff")
	7,"object/tangible/component/dna/dna_sample_very_low.iff")

	enum DamageType {
		KINETIC = 1,
		ENERGY = 2,
		BLAST = 4,
		STUN = 8,
		LIGHTSABER = 16,
		HEAT = 32,
		COLD = 64,
		ACID = 128,
		ELECTRICITY = 256
	};

	Example DNA Template:

	{quality = 0, source = "", level = 0,
		-- Stats
		hardiness = 0, fortitude = 0, dexterity = 0, endurance = 0, intellect = 0,
		cleverness = 0, dependability = 0, courage = 0, fierocity = 0, power = 0,

		-- Armor
		kinetic = 0,
		energy = 0,
		blast = 0,
		heat = 0,
		cold = 0,
		electric = 0,
		acid = 0,
		stun = 0,
		lightsaber = 0,

		-- Armor Rating
		armorRating = 0,

		-- Special Attacks
		special1 = "",
		special2 = "",

		ranged = false,

		-- Special Resists, read as Int
		specialResists = {},
	},
]]


dnaTests = {
	-- http://pets.furrycat.net/creature.html?ju6d14qq
	{"ju6d14qq",
		-- DNA 1
		{quality = 2, source = "greater sludge panther", level = 20,
			-- Stats
			hardiness = 484, fortitude = 112, dexterity = 440, endurance = 509, intellect = 445,
			cleverness = 244, dependability = 956, courage = 508, fierocity = 418, power = 308,

			-- Armor
			stun = -30,
			kinetic = 35,
			energy = 10,
			blast = 10,
			heat = -49,
			cold = -27,
			electric = -50,
			acid = 45,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "",

			ranged = false,

			-- Special Resists
			specialResists = {1, 128},
		},

		-- DNA 2
		{quality = 3, source = "greater sludge panther", level = 20,
			-- Stats
			hardiness = 478, fortitude = 109, dexterity = 443, endurance = 500, intellect = 448,
			cleverness = 235, dependability = 960, courage = 505, fierocity = 418, power = 304,

			-- Armor
			stun = -55,
			kinetic = 35,
			energy = 10,
			blast = 10,
			heat = -49,
			cold = -27,
			electric = -50,
			acid = 45,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "",

			ranged = false,

			-- Special Resists
			specialResists = {1, 128},
		},

		-- DNA 3
		{quality = 1, source = "shaupaut hunter", level = 20,
			-- Stats
			hardiness = 354, fortitude = 114, dexterity = 320, endurance = 518, intellect = 342,
			cleverness = 225, dependability = 1000, courage = 519, fierocity = 514, power = 265,

			-- Armor
			stun = -99,
			kinetic = 20,
			energy = 20,
			blast = 10,
			heat = -99,
			cold = 10,
			electric = -99,
			acid = 10,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "blindattack",
			special2 = "stunattack",

			ranged = false,

			-- Special Resists
			specialResists = {1, 2},
		},

		-- DNA 4
		{quality = 2, source = "corellian butterfly defender", level = 20,
			-- Stats
			hardiness = 125, fortitude = 60, dexterity = 124, endurance = 506, intellect = 130,
			cleverness = 190, dependability = 755, courage = 509, fierocity = 96, power = 270,

			-- Armor
			stun = -99,
			kinetic = 5,
			energy = 15,
			blast = -99,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists
			specialResists = {2},
		},

		-- DNA 5
		{quality = 2, source = "savage guf drolg", level = 20,
			-- Stats
			hardiness = 148, fortitude = 62, dexterity = 163, endurance = 514, intellect = 139,
			cleverness = 183, dependability = 763, courage = 510, fierocity = 104, power = 220,

			-- Armor
			stun = -99,
			kinetic = 10,
			energy = 5,
			blast = 5,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists
			specialResists = {1},
		}
	},

	-- http://pets.furrycat.net/creature.html?d5j7caq6
	{"d5j7caq6",
		-- DNA 1
		{quality = 1, source = "reclusive cavern spider queen", level = 20,
			-- Stats
			hardiness = 769, fortitude = 717, dexterity = 726, endurance = 516, intellect = 767,
			cleverness = 709, dependability = 512, courage = 516, fierocity = 471, power = 786,

			-- Armor
			kinetic = 60,
			energy = 60,
			blast = 60,
			heat = 50,
			cold = 20,
			electric = 20,
			acid = 20,
			stun = 20,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareapoison",
			special2 = "strongpoison",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 2
		{quality = 1, source = "reclusive cavern spider queen", level = 20,
			-- Stats
			hardiness = 644, fortitude = 720, dexterity = 706, endurance = 517, intellect = 675,
			cleverness = 708, dependability = 520, courage = 516, fierocity = 474, power = 790,

			-- Armor
			kinetic = 60,
			energy = 60,
			blast = 60,
			heat = 50,
			cold = 20,
			electric = 20,
			acid = 20,
			stun = 20,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareapoison",
			special2 = "strongpoison",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 3
		{quality = 1, source = "reclusive cavern spider queen", level = 20,
			-- Stats
			hardiness = 637, fortitude = 718, dexterity = 710, endurance = 515, intellect = 675,
			cleverness = 711, dependability = 510, courage = 510, fierocity = 469, power = 790,

			-- Armor
			kinetic = 60,
			energy = 60,
			blast = 60,
			heat = 50,
			cold = 20,
			electric = 20,
			acid = 20,
			stun = 20,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareapoison",
			special2 = "strongpoison",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 4
		{quality = 3, source = "reclusive cavern spider queen", level = 20,
			-- Stats
			hardiness = 759, fortitude = 705, dexterity = 713, endurance = 507, intellect = 759,
			cleverness = 697, dependability = 503, courage = 505, fierocity = 456, power = 776,

			-- Armor
			kinetic = 60,
			energy = 60,
			blast = 60,
			heat = 50,
			cold = 20,
			electric = 20,
			acid = 20,
			stun = 20,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareapoison",
			special2 = "strongpoison",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 5
		{quality = 2, source = "kimogila", level = 20,
			-- Stats
			hardiness = 659, fortitude = 629, dexterity = 609, endurance = 586, intellect = 568,
			cleverness = 434, dependability = 758, courage = 343, fierocity = 97, power = 605,

			-- Armor
			kinetic = 45,
			energy = 51,
			blast = 49,
			heat = 56,
			cold = 32,
			electric = 67,
			acid = 26,
			stun = 49,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "blindattack",
			special2 = "stunattack",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32, 64, 256, 128, 8},
		}
	},

	-- http://pets.furrycat.net/creature.html?ke5nbvgo
	{"ke5nbvgo",
		-- DNA 1
		{quality = 2, source = "greater sludge panther", level = 20,
			-- Stats
			cleverness = 238, endurance = 512, fierocity = 422, power = 311, intellect = 470,
			courage = 505, dependability = 956, dexterity = 448, fortitude = 115, hardiness = 491,

			-- Armor
			stun = -99,
			kinetic = 35,
			energy = 10,
			blast = 10,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = 45,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "",

			ranged = false,

			-- Special Resists
			specialResists = {1, 128},
		},
		-- DNA 2
		{quality = 3, source = "greater sludge panther", level = 20,
			-- Stats
			cleverness = 232, endurance = 499, fierocity = 414, power = 305, intellect = 452,
			courage = 506, dependability = 960, dexterity = 416, fortitude = 103, hardiness = 466,

			-- Armor
			stun = -99,
			kinetic = 35,
			energy = 10,
			blast = 10,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = 45,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "",

			ranged = false,

			-- Special Resists
			specialResists = {1, 128},
		},
		-- DNA 3
		{quality = 3, source = "kima", level = 10,
			-- Stats
			hardiness = 259, fortitude = 52, dexterity = 271, endurance = 503, intellect = 274,
			cleverness = 185, dependability = 758, courage = 505, fierocity = 100, power = 203,

			-- Armor
			kinetic = 15,
			energy = 20,
			blast = 5,
			heat = -99,
			cold = 5,
			electric = 5,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists
			specialResists = {1, 2},
		},
		-- DNA 4
		{quality = 2, source = "savage guf drolg", level = 15,
			-- Stats
			hardiness = 155, fortitude = 61, dexterity = 162, endurance = 504, intellect = 162,
			cleverness = 178, dependability = 761, courage = 506, fierocity = 105, power = 218,

			-- Armor
			kinetic = 10,
			energy = 5,
			blast = 5,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
		-- DNA 5
		{quality = 2, source = "savage guf drolg", level = 10,
			-- Stats
			hardiness = 276, fortitude = 64, dexterity = 302, endurance = 509, intellect = 290,
			cleverness = 194, dependability = 758, courage = 505, fierocity = 95, power = 203,

			-- Armor
			kinetic = 15,
			energy = 20,
			blast = 5,
			heat = -99,
			cold = 5,
			electric = 5,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2},
		}
	},

	-- http://pets.furrycat.net/creature.html?dcfolokr
	{"dcfolokr",
		-- DNA 1
		{quality = 1, source = "merek harvester", level = 50,
			-- Stats
			hardiness = 738, fortitude = 610, dexterity = 643, endurance = 513, intellect = 747,
			cleverness = 546, dependability = 765, courage = 509, fierocity = 97, power = 656,

			-- Armor
			kinetic = 75,
			energy = -99,
			blast = 10,
			heat = 10,
			cold = 10,
			electric = -99,
			acid = 10,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareacombo",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
		-- DNA 2
		{quality = 3, source = "merek harvester", level = 50,
			-- Stats
			hardiness = 735, fortitude = 607, dexterity = 632, endurance = 502, intellect = 747,
			cleverness = 539, dependability = 751, courage = 508, fierocity = 99, power = 656,

			-- Armor
			kinetic = 75,
			energy = -99,
			blast = 10,
			heat = 10,
			cold = 10,
			electric = -99,
			acid = 10,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "creatureareacombo",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
		-- DNA 3
		{quality = 3, source = "festering squill", level = 31,
			-- Stats
			hardiness = 367, fortitude = 159, dexterity = 403, endurance = 509, intellect = 406,
			cleverness = 285, dependability = 757, courage = 502, fierocity = 90, power = 388,

			-- Armor
			kinetic = 40,
			energy = 40,
			blast = 15,
			heat = -99,
			cold = 15,
			electric = 15,
			acid = 50,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "blindattack",
			special2 = "mediumdisease",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 128},
		},
		-- DNA 4
		{quality = 2, source = "corellian butterfly defender", level = 18,
			-- Stats
			hardiness = 126, fortitude = 57, dexterity = 134, endurance = 508, intellect = 129,
			cleverness = 191, dependability = 757, courage = 509, fierocity = 103, power = 266,

			-- Armor
			kinetic = 5,
			energy = 15,
			blast = -99,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {2},
		},
		-- DNA 5
		{quality = 2, source = "rancor", level = 50,
			-- Stats
			hardiness = 624, fortitude = 512, dexterity = 660, endurance = 514, intellect = 651,
			cleverness = 469, dependability = 514, courage = 509, fierocity = 556, power = 606,

			-- Armor
			kinetic = 30,
			energy = 30,
			blast = -99,
			heat = 60,
			cold = 60,
			electric = 60,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "stunattack",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 32, 64, 256},
		},
	},

	-- http://pets.furrycat.net/creature.html?jgbq7aiq
	{"jgbq7aiq",
		-- DNA 1
		{quality = 2, source = "mutant rancor", level = 75,
			-- Stats
			hardiness = 729, fortitude = 760, dexterity = 683, endurance = 507, intellect = 761,
			cleverness = 780, dependability = 510, courage = 507, fierocity = 649, power = 750,

			-- Armor
			kinetic = 45,
			energy = 60,
			blast = 25,
			heat = 100,
			cold = 100,
			electric = 100,
			acid = 25,
			stun = 25,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareableeding",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 32, 64, 256},
		},
		-- DNA 2
		{quality = 2, source = "mantigrue reaper", level = 50,
			-- Stats
			hardiness = 648, fortitude = 506, dexterity = 615, endurance = 509, intellect = 586,
			cleverness = 430, dependability = 757, courage = 505, fierocity = 99, power = 511,

			-- Armor
			kinetic = 40,
			energy = 40,
			blast = 70,
			heat = 0,
			cold = 70,
			electric = 70,
			acid = 70,
			stun = 70,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "",
			special2 = "",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 64, 256, 128, 8},
		},
		-- DNA 3
		{quality = 2, source = "mantigrue reaper", level = 50,
			-- Stats
			hardiness = 568, fortitude = 505, dexterity = 571, endurance = 504, intellect = 597,
			cleverness = 429, dependability = 756, courage = 511, fierocity = 102, power = 513,

			-- Armor
			kinetic = 40,
			energy = 40,
			blast = 70,
			heat = 0,
			cold = 70,
			electric = 70,
			acid = 70,
			stun = 70,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "",
			special2 = "",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 64, 256, 128, 8},
		},
		-- DNA 4
		{quality = 3, source = "insane mantigrue berserker", level = 50,
			-- Stats
			hardiness = 566, fortitude = 558, dexterity = 563, endurance = 508, intellect = 569,
			cleverness = 357, dependability = 1000, courage = 505, fierocity = 545, power = 567,

			-- Armor
			kinetic = 50,
			energy = 50,
			blast = 100,
			heat = 50,
			cold = -99,
			electric = 20,
			acid = 20,
			stun = 100,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "blindattack",
			special2 = "stunattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 8, 32, 128, 256},
		},
		-- DNA 5
		{quality = 1, source = "insane mantigrue berserker", level = 50,
			-- Stats
			hardiness = 572, fortitude = 563, dexterity = 574, endurance = 509, intellect = 576,
			cleverness = 364, dependability = 1000, courage = 510, fierocity = 556, power = 576,

			-- Armor
			kinetic = 50,
			energy = 50,
			blast = 100,
			heat = 50,
			cold = -99,
			electric = 20,
			acid = 20,
			stun = 100,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "blindattack",
			special2 = "stunattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 8, 32, 128, 256},
		},
	},

	-- http://pets.furrycat.net/creature.html?o97m0aan
	{"o97m0aan",
		-- DNA 1
		{quality = 3, source = "gaping spider queen", level = 47,
			-- Stats
			hardiness = 641, fortitude = 310, dexterity = 587, endurance = 499, intellect = 572,
			cleverness = 369, dependability = 501, courage = 508, fierocity = 510, power = 463,

			-- Armor
			kinetic = 65,
			energy = 65,
			blast = 40,
			heat = 25,
			cold = 30,
			electric = -99,
			acid = 30,
			stun = 30,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "knockdownattack",
			special2 = "mediumpoison",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 2
		{quality = 3, source = "gaping spider queen", level = 47,
			-- Stats
			hardiness = 645, fortitude = 304, dexterity = 583, endurance = 504, intellect = 570,
			cleverness = 373, dependability = 503, courage = 503, fierocity = 504, power = 462,

			-- Armor
			kinetic = 65,
			energy = 65,
			blast = 40,
			heat = 25,
			cold = 30,
			electric = -99,
			acid = 30,
			stun = 30,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "knockdownattack",
			special2 = "mediumpoison",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 3
		{quality = 3, source = "gaping spider hunter", level = 44,
			-- Stats
			hardiness = 556, fortitude = 506, dexterity = 636, endurance = 505, intellect = 635,
			cleverness = 408, dependability = 500, courage = 510, fierocity = 328, power = 546,

			-- Armor
			kinetic = 30,
			energy = 30,
			blast = 60,
			heat = 15,
			cold = -99,
			electric = -99,
			acid = 0,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "stunattack",
			special2 = "mediumpoison",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 4, 32},
		},
		-- DNA 4
		{quality = 1, source = "rhoa kwi guardian", level = 45,
			-- Stats
			hardiness = 589, fortitude = 316, dexterity = 590, endurance = 518, intellect = 656,
			cleverness = 387, dependability = 514, courage = 515, fierocity = 374, power = 430,

			-- Armor
			kinetic = 40,
			energy = 65,
			blast = 30,
			heat = 80,
			cold = 30,
			electric = 30,
			acid = 15,
			stun = 30,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "dizzyattack",

			ranged = true,

			-- Special Resists, read as Int
			specialResists = {1, 2, 32, 128},
		},
		-- DNA 5
		{quality = 2, source = "grassland voritor tracker", level = 45,
			-- Stats
			hardiness = 527, fortitude = 308, dexterity = 546, endurance = 509, intellect = 566,
			cleverness = 381, dependability = 757, courage = 506, fierocity = 101, power = 530,

			-- Armor
			kinetic = 65,
			energy = 65,
			blast = 30,
			heat = 30,
			cold = 30,
			electric = 30,
			acid = -99,
			stun = 30,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "posturedownattack",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2},
		},
	},

	-- http://pets.furrycat.net/creature.html?mmhkbp03
	{"mmhkbp03",
		-- DNA 1
		{quality = 2, source = "merek harvester", level = 50,
			-- Stats
			hardiness = 662, fortitude = 612, dexterity = 695, endurance = 513, intellect = 639,
			cleverness = 547, dependability = 761, courage = 514, fierocity = 102, power = 658,

			-- Armor
			kinetic = 75,
			energy = -99,
			blast = 10,
			heat = 10,
			cold = 10,
			electric = -99,
			acid = 10,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareacombo",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
		-- DNA 2
		{quality = 2, source = "merek harvester", level = 50,
			-- Stats
			hardiness = 647, fortitude = 606, dexterity = 633, endurance = 504, intellect = 647,
			cleverness = 544, dependability = 759, courage = 507, fierocity = 103, power = 656,

			-- Armor
			kinetic = 75,
			energy = -99,
			blast = 10,
			heat = 10,
			cold = 10,
			electric = -99,
			acid = 10,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareacombo",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
		-- DNA 3
		{quality = 1, source = "gronda", level = 19,
			-- Stats
			hardiness = 346, fortitude = 61, dexterity = 286, endurance = 515, intellect = 303,
			cleverness = 196, dependability = 762, courage = 519, fierocity = 150, power = 222,

			-- Armor
			kinetic = 20,
			energy = 15,
			blast = 5,
			heat = -99,
			cold = -99,
			electric = -99,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 0,

			-- Special Attacks
			special1 = "",
			special2 = "knockdownattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2},
		},
		-- DNA 4
		{quality = 3, source = "rancor", level = 50,
			-- Stats
			hardiness = 686, fortitude = 504, dexterity = 668, endurance = 507, intellect = 614,
			cleverness = 471, dependability = 500, courage = 505, fierocity = 545, power = 609,

			-- Armor
			kinetic = 30,
			energy = 30,
			blast = -99,
			heat = 60,
			cold = 60,
			electric = 60,
			acid = -99,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "stunattack",
			special2 = "intimidationattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1, 2, 32, 64, 256},
		},
		-- DNA 5
		{quality = 2, source = "merek harvester", level = 55,
			-- Stats
			hardiness = 645, fortitude = 614, dexterity = 634, endurance = 507, intellect = 651,
			cleverness = 550, dependability = 760, courage = 512, fierocity = 103, power = 657,

			-- Armor
			kinetic = 75,
			energy = -99,
			blast = 10,
			heat = 10,
			cold = 10,
			electric = -99,
			acid = 10,
			stun = -99,
			lightsaber = -99,

			-- Armor Rating
			armorRating = 1,

			-- Special Attacks
			special1 = "creatureareacombo",
			special2 = "dizzyattack",

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {1},
		},
	}
}
