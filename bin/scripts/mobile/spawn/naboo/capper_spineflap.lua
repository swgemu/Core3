capper_spineflap = {
	wanderRadius = 10,
	commandLevel = 0,
	
	size = 1,
	
	type = PACK,
	
	scout = {},
	scoutWeight = 0.00,
	
	protector = {"capper_spineflap"},
	protectorWeight = 1.00,
	
	baby = {},
	babyWeight = 0.00,
	
	lairTemplate = ""
}

addDynamicGroup("capper_spineflap", capper_spineflap);

capper_spineflap = {
	wanderRadius = 10,
	commandLevel = 0,
	
	respawnTime = 60;
	
	type = HERD,
	
	x = 0.00,
	y = 0.00,
	z = 6.00,
	cellID = 0,
	
	spawns = {
		{"capper_spineflap",0.00,0.00,0.00,0.00,0.00,0.00,0.00},
		{"capper_spineflap",1.00,1.00,0.00,0.00,0.00,0.00,0.00}
	}
}

addStaticGroup("capper_spineflap", capper_spineflap);