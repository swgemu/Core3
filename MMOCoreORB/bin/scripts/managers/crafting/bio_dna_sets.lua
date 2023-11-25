--[[ Added Tests
	http://pets.furrycat.net/

	"FurryCat Test - ju6d14qq", "ju6d14qq",
	"FurryCat Test - d5j7caq6", "d5j7caq6",
	"FurryCat Test - ke5nbvgo", "ke5nbvgo",

	1,"object/tangible/component/dna/dna_sample_very_high.iff")
	2,"object/tangible/component/dna/dna_sample_high.iff")
	3,"object/tangible/component/dna/dna_sample_above_average.iff")
	4,"object/tangible/component/dna/dna_sample_average.iff")
	5,"object/tangible/component/dna/dna_sample_below_average.iff")
	6,"object/tangible/component/dna/dna_sample_low.iff")
	7,"object/tangible/component/dna/dna_sample_very_low.iff")


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
			cleverness = 244, endurance = 509, fierocity = 418, power = 308, intellect = 445,
			courage = 508, dependability = 956, dexterity = 440, fortitude = 112, hardiness = 484,

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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ACID_DAMAGE},
		},

		-- DNA 2
		{quality = 3, source = "greater sludge panther", level = 20,
			-- Stats
			cleverness = 235, endurance = 500, fierocity = 418, power = 304, intellect = 448,
			courage = 505, dependability = 960, dexterity = 443, fortitude = 109, hardiness = 478,

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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ACID_DAMAGE},
		},

		-- DNA 3
		{quality = 1, source = "shaupaut hunter", level = 20,
			-- Stats
			cleverness = 225, endurance = 518, fierocity = 514, power = 265, intellect = 342,
			courage = 519, dependability = 1000, dexterity = 320, fortitude = 114, hardiness = 354,

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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ENRGY_DAMAGE},
		},

		-- DNA 4
		{quality = 2, source = "corellian butterfly defender", level = 20,
			-- Stats
			cleverness = 190, endurance = 506, fierocity = 96, power = 270, intellect = 130,
			courage = 509, dependability = 755, dexterity = 124, fortitude = 60, hardiness = 125,

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

			ranged = false,

			-- Special Resists
			specialResists = {ENRGY_DAMAGE},
		},

		-- DNA 5
		{quality = 2, source = "savage guf drolg", level = 20,
			-- Stats
			cleverness = 183, endurance = 514, fierocity = 104, power = 220, intellect = 139,
			courage = 510, dependability = 960, dexterity = 763, fortitude = 62, hardiness = 148,

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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE, BLAST_DAMAGE, HEAT_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE, BLAST_DAMAGE, HEAT_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE, BLAST_DAMAGE, HEAT_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE, BLAST_DAMAGE, HEAT_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE, BLAST_DAMAGE, HEAT_DAMAGE, COLD_DAMAGE, ELECTRICITY_DAMAGE, ACID_DAMAGE, STUN_DAMAGE},
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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ACID_DAMAGE},
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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ACID_DAMAGE},
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

			ranged = false,

			-- Special Resists
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE},
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

			ranged = false,

			-- Special Resists, read as Int
			specialResists = {KINETIC_DAMAGE, ENERGY_DAMAGE},
		}
	}
}
