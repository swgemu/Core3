ndc_transport_tier4 = ShipAgent:new {
	template = "transport_science_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 1,

	spaceFaction = "rsf",
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_tier4, "ndc_transport_tier4")
