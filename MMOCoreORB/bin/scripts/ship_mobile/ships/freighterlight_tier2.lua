freighterlight_tier2 = ShipAgent:new {
	template = "freighterlight_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"rsf", "corsec"},
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterlight_tier2, "freighterlight_tier2")
