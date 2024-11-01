hidden_daggers_eliminator_tier2 = ShipAgent:new {
	template = "hutt_light_s01_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_hutt_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "hutt", "valarian", "rsf", "corsec"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	appearance = "hiddendagger_pilots",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hidden_daggers_eliminator_tier2, "hidden_daggers_eliminator_tier2")
