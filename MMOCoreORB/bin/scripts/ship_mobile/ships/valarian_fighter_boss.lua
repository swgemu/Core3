valarian_fighter_boss = ShipAgent:new {
	template = "hutt_light_s02_tier4",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 2949.12,

	lootChance = 0.126,
	lootRolls = 1,
	lootTable = "space_valarian_tier4",

	minCredits = 200,
	maxCredits = 500,

	aggressive = 1,

	spaceFaction = "valarian",
	alliedFactions = {"valarian"},
	enemyFactions = {"imperial", "civilian", "merchant", "hutt", "pirate", "rebel", "blacksun", "borvo", "corsec", "rsf"},

	color1 = 32,
	color2 = 35,
	texture = 3,
	appearance = "valarian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(valarian_fighter_boss, "valarian_fighter_boss")
