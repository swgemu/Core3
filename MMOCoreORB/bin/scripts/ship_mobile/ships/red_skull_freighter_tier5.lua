red_skull_freighter_tier5 = ShipAgent:new {
	template = "freighterheavy_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier5",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "pirate",

	color1 = 0,
	color2 = 0,
	texture = 0,
	appearance = "generic_pirate",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(red_skull_freighter_tier5, "red_skull_freighter_tier5")
