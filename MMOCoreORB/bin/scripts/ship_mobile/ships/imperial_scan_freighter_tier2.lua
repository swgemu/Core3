imperial_scan_freighter_tier2 = ShipAgent:new {
	template = "freightermedium_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_imperial_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "imperial",
	imperialFactionReward = -20,
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(imperial_scan_freighter_tier2, "imperial_scan_freighter_tier2")
