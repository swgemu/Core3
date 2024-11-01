hidden_daggers_killer_tier2 = ShipAgent:new {
	template = "blacksun_heavy_s01_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "fighter",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 33,
	color2 = 55,
	texture = 6,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_killer_tier2, "hidden_daggers_killer_tier2")
