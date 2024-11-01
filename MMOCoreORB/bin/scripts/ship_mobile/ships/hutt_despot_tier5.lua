hutt_despot_tier5 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "capital",

	experience = 26843.55,

	lootChance = 0.52,
	lootRolls = 1,
	lootTable = "space_hutt_tier5",

	minCredits = 617,
	maxCredits = 1100,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_despot_tier5, "hutt_despot_tier5")
