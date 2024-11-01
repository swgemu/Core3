red_skull_pirate_heavy = ShipAgent:new {
	template = "hutt_heavy_s02_tier4",
	pilotTemplate = "heavy_fighter_tier4",
	shipType = "fighter",

	experience = 4259.84,

	lootChance = 0.182,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 280,
	maxCredits = 650,

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

ShipAgentTemplates:addShipAgentTemplate(red_skull_pirate_heavy, "red_skull_pirate_heavy")
