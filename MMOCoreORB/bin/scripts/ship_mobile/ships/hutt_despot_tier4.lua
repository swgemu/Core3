hutt_despot_tier4 = ShipAgent:new {
	template = "smuggler_warlord_ship_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "capital",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 465,
	maxCredits = 950,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_despot_tier4, "hutt_despot_tier4")
