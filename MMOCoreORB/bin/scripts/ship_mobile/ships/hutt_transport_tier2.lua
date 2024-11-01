hutt_transport_tier2 = ShipAgent:new {
	template = "hutt_transport_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_hutt_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "hutt",
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_transport_tier2, "hutt_transport_tier2")
