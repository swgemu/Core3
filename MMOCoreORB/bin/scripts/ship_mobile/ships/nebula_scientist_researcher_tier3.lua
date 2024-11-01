nebula_scientist_researcher_tier3 = ShipAgent:new {
	template = "transport_science_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "imperial",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_researcher_tier3, "nebula_scientist_researcher_tier3")
