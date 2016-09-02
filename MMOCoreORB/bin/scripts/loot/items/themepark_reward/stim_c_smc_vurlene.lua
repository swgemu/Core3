stim_c_smc_vurlene = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/tangible/medicine/crafted/medpack_damage_c.iff",

	craftingValues = {
		{"power",150,300,0},
		{"charges",5,10,0},
		{"skillmodmin",40,55,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	--TODO: HOW DO WE VARY WHAT STATS & TYPES OF THINGS THESE CAN HEAL? (re: mind, poison, etc. )
}

addLootItemTemplate("stim_c_smc_vurlene", stim_c_smc_vurlene)