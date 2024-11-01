hutt_despot_tier2 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "capital",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_hutt_tier2",

	minCredits = 170,
	maxCredits = 368,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"blacksun", "valarian", "pirate", "imperial"},
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_despot_tier2, "hutt_despot_tier2")
