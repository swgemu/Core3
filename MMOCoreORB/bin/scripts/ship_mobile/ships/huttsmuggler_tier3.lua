huttsmuggler_tier3 = ShipAgent:new {
	template = "hutt_medium_s02_tier3",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_hutt_tier3",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 1,

	spaceFaction = "hutt",
	alliedFactions = {"hutt"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "valarian", "pirate", "rsf", "corsec", "blacksun"},

	color1 = 37,
	color2 = 23,
	texture = 3,
	questLoot = "hutt_smuggler",
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(huttsmuggler_tier3, "huttsmuggler_tier3")
