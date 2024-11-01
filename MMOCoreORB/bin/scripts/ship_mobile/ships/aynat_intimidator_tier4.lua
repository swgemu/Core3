aynat_intimidator_tier4 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 63,
	color2 = 11,
	texture = 0,
	appearance = "aynat_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(aynat_intimidator_tier4, "aynat_intimidator_tier4")
