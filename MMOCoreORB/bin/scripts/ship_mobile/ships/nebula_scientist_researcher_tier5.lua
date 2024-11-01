nebula_scientist_researcher_tier5 = ShipAgent:new {
	template = "transport_science_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "imperial",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(nebula_scientist_researcher_tier5, "nebula_scientist_researcher_tier5")
