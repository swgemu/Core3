crystal_smuggler_yt1300_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "fighter",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_civilian_tier2",

	minCredits = 95,
	maxCredits = 240,

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

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_yt1300_tier2, "crystal_smuggler_yt1300_tier2")
