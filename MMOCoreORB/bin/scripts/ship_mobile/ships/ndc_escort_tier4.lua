ndc_escort_tier4 = ShipAgent:new {
	template = "tiefighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 1,

	spaceFaction = "rsf",
	alliedFactions = {"corsec", "imperial", "rsf"},
	enemyFactions = {"rebel", "civilian", "merchant", "valarian", "pirate", "blacksun", "borvo"},
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_escort_tier4, "ndc_escort_tier4")
