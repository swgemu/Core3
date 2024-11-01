hutt_despot_tier3 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "capital",

	experience = 5120,

	lootChance = 0.6,
	lootRolls = 1,
	lootTable = "space_hutt_tier3",

	minCredits = 94,
	maxCredits = 700,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_despot_tier3, "hutt_despot_tier3")
