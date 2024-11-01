smuggler_yt1300_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 95,
	maxCredits = 240,

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

ShipAgentTemplates:addShipAgentTemplate(smuggler_yt1300_tier2, "smuggler_yt1300_tier2")
