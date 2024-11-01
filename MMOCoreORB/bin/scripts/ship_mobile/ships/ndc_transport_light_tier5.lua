ndc_transport_light_tier5 = ShipAgent:new {
	template = "yt1300_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "bomber",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 975,

	aggressive = 1,

	spaceFaction = "rsf",

	color1 = 63,
	color2 = 12,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_transport_light_tier5, "ndc_transport_light_tier5")
