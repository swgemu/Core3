endor_contraband_transport_tier1 = ShipAgent:new {
	template = "hutt_transport_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_hutt_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "hutt",

	color1 = 0,
	color2 = 15,
	texture = 6,
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(endor_contraband_transport_tier1, "endor_contraband_transport_tier1")
