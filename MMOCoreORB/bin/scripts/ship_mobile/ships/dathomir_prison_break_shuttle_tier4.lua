dathomir_prison_break_shuttle_tier4 = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial"},

	color1 = 0,
	color2 = 10,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dathomir_prison_break_shuttle_tier4, "dathomir_prison_break_shuttle_tier4")
