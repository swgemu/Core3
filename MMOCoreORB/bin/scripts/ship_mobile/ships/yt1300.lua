yt1300 = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_merchant_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "merchant",

	color1 = 0,
	color2 = 63,
	texture = 0,
	formationLocation = 3,
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(yt1300, "yt1300")
