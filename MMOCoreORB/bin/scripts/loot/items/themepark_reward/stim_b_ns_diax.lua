stim_b_ns_diax = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/tangible/medicine/crafted/medpack_damage_b.iff",

	craftingValues = {
		{"power",75,200,0},
		{"charges",5,10,0},
		{"skillmodmin",35,50,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	--TODO: HOW DO WE VARY WHAT STATS & TYPES OF THINGS THESE CAN HEAL? (re: mind, poison, etc. )
}

addLootItemTemplate("stim_b_ns_diax", stim_b_ns_diax)