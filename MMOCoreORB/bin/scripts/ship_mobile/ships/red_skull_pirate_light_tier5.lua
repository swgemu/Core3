red_skull_pirate_light_tier5 = ShipAgent:new {
	template = "hutt_light_s02_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate"},
	enemyFactions = {"imperial", "rebel", "civilian", "merchant", "rsf", "corsec", "hutt", "blacksun"},

	color1 = 7,
	color2 = 32,
	texture = 3,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(red_skull_pirate_light_tier5, "red_skull_pirate_light_tier5")
