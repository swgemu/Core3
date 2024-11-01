freightermedium_tier3 = ShipAgent:new {
	template = "freightermedium_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"rsf", "corsec"},
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freightermedium_tier3, "freightermedium_tier3")
