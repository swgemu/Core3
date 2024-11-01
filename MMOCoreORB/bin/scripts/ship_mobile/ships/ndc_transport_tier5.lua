ndc_transport_tier5 = ShipAgent:new {
	template = "transport_science_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 1,

	spaceFaction = "rsf",
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_tier5, "ndc_transport_tier5")
