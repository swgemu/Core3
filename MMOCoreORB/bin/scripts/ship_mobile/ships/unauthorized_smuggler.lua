unauthorized_smuggler = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_civilian_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 1,

	spaceFaction = "civilian",

	color1 = 38,
	color2 = 40,
	texture = 2,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(unauthorized_smuggler, "unauthorized_smuggler")
