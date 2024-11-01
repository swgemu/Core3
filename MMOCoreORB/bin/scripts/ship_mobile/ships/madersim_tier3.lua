madersim_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "bomber",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "rsf",
	alliedFactions = {"rsf"},
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(madersim_tier3, "madersim_tier3")
