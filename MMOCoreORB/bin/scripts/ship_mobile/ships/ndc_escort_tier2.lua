ndc_escort_tier2 = ShipAgent:new {
	template = "tiefighter_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.16,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 1,

	spaceFaction = "rsf",
	alliedFactions = {"corsec", "imperial", "rsf"},
	enemyFactions = {"rebel", "civilian", "merchant", "valarian", "pirate", "blacksun", "borvo"},
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_escort_tier2, "ndc_escort_tier2")
