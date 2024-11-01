naboo_diplomatic_corps_bad_tier3 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 95,
	maxCredits = 240,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 63,
	color2 = 12,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(naboo_diplomatic_corps_bad_tier3, "naboo_diplomatic_corps_bad_tier3")
