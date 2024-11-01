aynat_intimidator_tier3 = ShipAgent:new {
	template = "blacksun_heavy_s02_tier3",
	pilotTemplate = "heavy_fighter_tier3",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 160,
	maxCredits = 353,

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

ShipAgentTemplates:addShipAgentTemplate(aynat_intimidator_tier3, "aynat_intimidator_tier3")
