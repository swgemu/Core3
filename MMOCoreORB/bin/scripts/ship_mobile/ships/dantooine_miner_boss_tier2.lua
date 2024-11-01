dantooine_miner_boss_tier2 = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier3",
	shipType = "bomber",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_pirate_tier3",

	minCredits = 75,
	maxCredits = 160,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_boss_tier2, "dantooine_miner_boss_tier2")
