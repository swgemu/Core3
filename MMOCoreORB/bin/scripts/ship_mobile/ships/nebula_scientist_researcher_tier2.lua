nebula_scientist_researcher_tier2 = ShipAgent:new {
	template = "transport_science_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_researcher_tier2, "nebula_scientist_researcher_tier2")
