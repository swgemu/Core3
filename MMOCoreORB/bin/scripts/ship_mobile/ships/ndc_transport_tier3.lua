ndc_transport_tier3 = ShipAgent:new {
	template = "transport_science_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 1,

	spaceFaction = "rsf",
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_tier3, "ndc_transport_tier3")
