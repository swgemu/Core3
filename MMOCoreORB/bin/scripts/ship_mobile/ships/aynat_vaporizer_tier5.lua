aynat_vaporizer_tier5 = ShipAgent:new {
	template = "hutt_heavy_s02_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "bomber",

	experience = 8724.15,

	lootChance = 0.169,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 465,
	maxCredits = 925,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},

	color1 = 63,
	color2 = 63,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(aynat_vaporizer_tier5, "aynat_vaporizer_tier5")
