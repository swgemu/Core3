crystal_smuggler_yt1300_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_civilian_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial"},

	color1 = 34,
	color2 = 24,
	texture = 2,
	questLoot = "glowing_crystals",
	appearance = "coynite_pilot",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_yt1300_tier3, "crystal_smuggler_yt1300_tier3")
