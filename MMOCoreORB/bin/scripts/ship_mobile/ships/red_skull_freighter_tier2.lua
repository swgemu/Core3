red_skull_freighter_tier2 = ShipAgent:new {
	template = "freighterheavy_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier2",

	minCredits = 75,
	maxCredits = 160,

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

ShipAgentTemplates:addShipAgentTemplate(red_skull_freighter_tier2, "red_skull_freighter_tier2")
