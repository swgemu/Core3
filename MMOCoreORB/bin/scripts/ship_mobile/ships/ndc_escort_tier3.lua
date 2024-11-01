ndc_escort_tier3 = ShipAgent:new {
	template = "tiefighter_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "rsf",
	alliedFactions = {"corsec", "imperial", "rsf"},
	enemyFactions = {"rebel", "civilian", "merchant", "valarian", "pirate", "blacksun", "borvo"},
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_escort_tier3, "ndc_escort_tier3")
