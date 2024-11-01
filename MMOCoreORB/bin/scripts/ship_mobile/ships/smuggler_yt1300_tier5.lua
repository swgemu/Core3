smuggler_yt1300_tier5 = ShipAgent:new {
	template = "yt1300_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 975,

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

ShipAgentTemplates:addShipAgentTemplate(smuggler_yt1300_tier5, "smuggler_yt1300_tier5")
