nebula_scientist_researcher_tier1 = ShipAgent:new {
	template = "transport_science_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "imperial",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_researcher_tier1, "nebula_scientist_researcher_tier1")
