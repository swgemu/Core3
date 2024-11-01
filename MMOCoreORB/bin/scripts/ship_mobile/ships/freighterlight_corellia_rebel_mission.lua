freighterlight_corellia_rebel_mission = ShipAgent:new {
	template = "freighterlight_tier4",
	pilotTemplate = "heavy_tier4",
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
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterlight_corellia_rebel_mission, "freighterlight_corellia_rebel_mission")
