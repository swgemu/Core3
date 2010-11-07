capper_spineflap = {
	wanderRadius = 10,
	commandLevel = 0,
	
	size = 1,
	
	type = PACK,
	
	scout = {"capper_spineflap"},
	scoutWeight = 1.00,
	
	protector = {},
	protectorWeight = 0.00,
	
	baby = {},
	babyWeight = 0.00,
	
	lairTemplate = ""
}

addDynamicGroup("capper_spineflap", capper_spineflap);

capper_spineflap = {
	commandLevel = 0,
	
	type = HERD,
	
	spawns = {
		{
			name = "capper_spineflap",
			x = 0.00,
			y = 0.00,
			z = 0.00,
			ow = 0.00,
			ox = 0.00,
			oy = 0.00,
			oz = 0.00,
			cellID = 0
		},
		{
			name = "capper_spineflap",
			x = 1.00,
			y = 1.00,
			z = 1.00,
			ow = 0.00,
			ox = 0.00,
			oy = 0.00,
			oz = 0.00,
			cellID = 0
		}
	}
}

addStaticGroup("capper_spineflap", capper_spineflap);