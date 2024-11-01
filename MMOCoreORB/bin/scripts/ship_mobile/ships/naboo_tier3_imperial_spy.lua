naboo_tier3_imperial_spy = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "bomber",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_imperial_tier1",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "civilian",
	questLoot = "experiment_information",
	appearance = "imperial_officer",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(naboo_tier3_imperial_spy, "naboo_tier3_imperial_spy")
