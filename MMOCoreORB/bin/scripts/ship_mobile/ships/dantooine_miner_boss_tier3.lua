dantooine_miner_boss_tier3 = ShipAgent:new {
	template = "xwing_tier3",
	pilotTemplate = "medium_fighter_tier4",
	shipType = "bomber",

	experience = 1408,

	lootChance = 0.165,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 150,
	maxCredits = 323,

	aggressive = 0,

	spaceFaction = "civilian",
	alliedFactions = {"civilian"},
	color2 = 63,
	texture = 2,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_boss_tier3, "dantooine_miner_boss_tier3")
