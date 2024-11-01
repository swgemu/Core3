imperial_engineer = ShipAgent:new {
	template = "tiefighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial", "civilian", "merchant"},
	enemyFactions = {"rebel", "nym", "pirate", "hutt", "valarian", "borvo", "aynat", "blacksun"},
	imperialFactionReward = -54,
	rebelFactionReward = 27,
	appearance = "imperial_officer",
}

ShipAgentTemplates:addShipAgentTemplate(imperial_engineer, "imperial_engineer")
