velocity_smuggler = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "bomber",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 60,
	maxCredits = 120,

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

ShipAgentTemplates:addShipAgentTemplate(velocity_smuggler, "velocity_smuggler")
