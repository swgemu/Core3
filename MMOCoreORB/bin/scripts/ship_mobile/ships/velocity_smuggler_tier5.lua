velocity_smuggler_tier5 = ShipAgent:new {
	template = "yt1300_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "bomber",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_civilian_tier5",

	minCredits = 465,
	maxCredits = 975,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 5,
	color2 = 42,
	texture = 1,
	appearance = "velocity_pilots",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(velocity_smuggler_tier5, "velocity_smuggler_tier5")
