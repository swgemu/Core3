hutt_freighterheavy_tier5 = ShipAgent:new {
	template = "freighterheavy_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_hutt_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "hutt",
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_freighterheavy_tier5, "hutt_freighterheavy_tier5")
