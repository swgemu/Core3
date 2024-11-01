dantooine_miner_boss_tier1 = ShipAgent:new {
	template = "xwing_tier1",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "bomber",

	experience = 110,

	lootChance = 0.187,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 55,
	maxCredits = 110,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_boss_tier1, "dantooine_miner_boss_tier1")
