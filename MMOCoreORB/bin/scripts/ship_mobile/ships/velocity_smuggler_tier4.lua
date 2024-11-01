velocity_smuggler_tier4 = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "bomber",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 400,
	maxCredits = 800,

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

ShipAgentTemplates:addShipAgentTemplate(velocity_smuggler_tier4, "velocity_smuggler_tier4")
