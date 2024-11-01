velocity_smuggler_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 95,
	maxCredits = 240,

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

ShipAgentTemplates:addShipAgentTemplate(velocity_smuggler_tier2, "velocity_smuggler_tier2")
