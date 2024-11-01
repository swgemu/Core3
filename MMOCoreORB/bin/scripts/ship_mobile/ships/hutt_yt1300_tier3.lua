hutt_yt1300_tier3 = ShipAgent:new {
	template = "yt1300_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "space_hutt_tier3",

	minCredits = 200,
	maxCredits = 480,

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

ShipAgentTemplates:addShipAgentTemplate(hutt_yt1300_tier3, "hutt_yt1300_tier3")
