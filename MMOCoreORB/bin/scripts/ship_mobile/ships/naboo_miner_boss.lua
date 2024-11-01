naboo_miner_boss = ShipAgent:new {
	template = "hutt_light_s02_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 90,

	lootChance = 0.153,
	lootRolls = 1,
	lootTable = "space_story_naboo_miner",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian", "imperial", "hutt", "rebel"},
	enemyFactions = {"pirate"},
	color2 = 23,
	texture = 4,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(naboo_miner_boss, "naboo_miner_boss")
