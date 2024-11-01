yt1300_smuggler = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_civilian_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "civilian",

	color1 = 63,
	color2 = 0,
	texture = 1,
	appearance = "civilian",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
	tauntAggressiveness = 0.05,
}

ShipAgentTemplates:addShipAgentTemplate(yt1300_smuggler, "yt1300_smuggler")
