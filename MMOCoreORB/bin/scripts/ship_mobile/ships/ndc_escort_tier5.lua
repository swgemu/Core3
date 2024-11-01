ndc_escort_tier5 = ShipAgent:new {
	template = "tiefighter_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6710.89,

	lootChance = 0.13,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 425,
	maxCredits = 825,

	aggressive = 1,

	spaceFaction = "rsf",
	alliedFactions = {"corsec", "imperial", "rsf"},
	enemyFactions = {"rebel", "civilian", "merchant", "valarian", "pirate", "blacksun", "borvo"},
	questLoot = "encrypted_documents",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(ndc_escort_tier5, "ndc_escort_tier5")
