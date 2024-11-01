imperial_cargo_tower = ShipAgent:new {
	template = "freighterheavy_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -40,
	appearance = "imperial_pilot",
}

ShipAgentTemplates:addShipAgentTemplate(imperial_cargo_tower, "imperial_cargo_tower")
