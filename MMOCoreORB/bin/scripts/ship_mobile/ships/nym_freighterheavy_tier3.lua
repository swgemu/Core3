nym_freighterheavy_tier3 = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_nym_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "nym",
	appearance = "nym",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_freighterheavy_tier3, "nym_freighterheavy_tier3")
