ndc_transport_light_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "bomber",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 1,

	spaceFaction = "rsf",

	color1 = 63,
	color2 = 12,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_light_tier3, "ndc_transport_light_tier3")
