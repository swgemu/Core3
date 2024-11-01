ndc_transport_light_tier1 = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 1,

	spaceFaction = "rsf",

	color1 = 63,
	color2 = 12,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_light_tier1, "ndc_transport_light_tier1")
