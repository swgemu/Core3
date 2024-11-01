cloak_representative_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "transport",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},

	color1 = 5,
	color2 = 42,
	texture = 1,
	formationLocation = 2,
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(cloak_representative_tier3, "cloak_representative_tier3")
