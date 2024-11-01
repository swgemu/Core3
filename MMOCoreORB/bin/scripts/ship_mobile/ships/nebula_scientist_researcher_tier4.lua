nebula_scientist_researcher_tier4 = ShipAgent:new {
	template = "transport_science_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "imperial",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_researcher_tier4, "nebula_scientist_researcher_tier4")
