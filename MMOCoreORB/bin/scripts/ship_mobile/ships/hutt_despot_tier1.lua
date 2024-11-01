hutt_despot_tier1 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "capital",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_hutt_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_despot_tier1, "hutt_despot_tier1")
