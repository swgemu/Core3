smuggler_yt1300_tier4 = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 0,

	spaceFaction = "smuggler",

	color1 = 47,
	color2 = 55,
	texture = 1,
	appearance = "civilian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(smuggler_yt1300_tier4, "smuggler_yt1300_tier4")
