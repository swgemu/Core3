stim_d_smc_vurlene = {
	minimumLevel = 0,
	maximumLevel = 0,
	customObjectName = "",
	directObjectTemplate = "object/tangible/medicine/crafted/medpack_damage_d.iff",

	craftingValues = {
		{"power",200,400,0},
		{"charges",5,10,0},
		{"skillmodmin",45,60,0},
	},
	customizationStringNames = {},
	customizationValues = {},
	--TODO: HOW DO WE VARY WHAT STATS & TYPES OF THINGS THESE CAN HEAL? (re: mind, poison, etc. )
}

addLootItemTemplate("stim_d_smc_vurlene", stim_d_smc_vurlene)