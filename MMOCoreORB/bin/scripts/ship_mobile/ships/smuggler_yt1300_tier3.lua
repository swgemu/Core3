smuggler_yt1300_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 200,
	maxCredits = 480,

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

ShipAgentTemplates:addShipAgentTemplate(smuggler_yt1300_tier3, "smuggler_yt1300_tier3")
