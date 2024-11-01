bestine_pirate_leader_tier3 = ShipAgent:new {
	template = "z95_tier4",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_story_tatooine_bestine_pirates",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "valarian"},
	color2 = 8,
	texture = 1,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(bestine_pirate_leader_tier3, "bestine_pirate_leader_tier3")
