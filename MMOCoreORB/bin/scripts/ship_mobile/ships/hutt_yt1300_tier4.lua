hutt_yt1300_tier4 = ShipAgent:new {
	template = "yt1300_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "fighter",

	experience = 6553.6,

	lootChance = 0.28,
	lootRolls = 1,
	lootTable = "space_hutt_tier4",

	minCredits = 400,
	maxCredits = 800,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "valarian", "pirate", "rsf", "corsec", "blacksun"},

	color1 = 23,
	color2 = 23,
	texture = 2,
	questLoot = "hutt_smuggler",
	appearance = "hutt",

	tauntType = "hutt",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_yt1300_tier4, "hutt_yt1300_tier4")
