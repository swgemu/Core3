-- The following are the server-side ratios for experience conversion. Key is the string regex used to find the experience,
-- and should be as specific as possible to avoid duplications. Value is the ratio (from x:1) for conversion.

combat = 
	{
		{"combat_general", 3},
		{"squadleader", 90},
		{"bountyhunter", 1},
		{"combat_melee", 30},
		{"combat_ranged", 30}
	}
	
senses = 
	{
		{"bio_engineer_dna_harvesting", 3},
		{"political", 3},
		{"slicing", 3},
		{"merchant", 4},
		{"resource_harvesting_inorganic", 5},
		{"imagedesigner", 7},
		{"scout", 8},
		{"creaturehandler", 9},
		{"dance", 10},
		{"music", 10},
		{"entertainer_healing", 10},
		{"camp", 10},
		{"medical", 10},
		{"trapping", 25},
		
	}

crafting = 
	{
		{"crafting_bio_engineer_creature", 4},
		{"crafting_bio_engineer_tissue", 5},
		{"crafting_c", 5},
		{"crafting_d", 5},
		{"crafting_f", 5},
		{"crafting_m", 5},
		{"crafting_sc", 5},
		{"crafting_sp", 5},
		{"crafting_w", 5},
		{"crafting_general", 8},
		{"crafting_structure_general", 35}
	}