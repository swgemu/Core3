ndc_escort_tier1 = ShipAgent:new {
	template = "tiefighter_tier1",
	pilotTemplate = "light_fighter_tier1",
	shipType = "fighter",

	experience = 100,

	lootChance = 0.17,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 51,
	maxCredits = 103,

	aggressive = 1,

	spaceFaction = "rsf",
	alliedFactions = {"corsec", "imperial", "rsf"},
	enemyFactions = {"rebel", "civilian", "merchant", "valarian", "pirate", "blacksun", "borvo"},
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_escort_tier1, "ndc_escort_tier1")
