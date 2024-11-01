endor_contraband_transport_tier4 = ShipAgent:new {
	template = "hutt_transport_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_hutt_tier4",

	minCredits = 16,
	maxCredits = 200,

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

ShipAgentTemplates:addShipAgentTemplate(endor_contraband_transport_tier4, "endor_contraband_transport_tier4")
