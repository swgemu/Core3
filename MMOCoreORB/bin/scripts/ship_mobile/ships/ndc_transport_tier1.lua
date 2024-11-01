ndc_transport_tier1 = ShipAgent:new {
	template = "transport_science_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier2",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 1,

	spaceFaction = "rsf",
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_tier1, "ndc_transport_tier1")
