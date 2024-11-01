yavin_mining_executive_transport_tier2 = ShipAgent:new {
	template = "transport_science_tier2",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "merchant",
	appearance = "civilian",
}

ShipAgentTemplates:addShipAgentTemplate(yavin_mining_executive_transport_tier2, "yavin_mining_executive_transport_tier2")
