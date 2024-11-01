dantooine_miner_boss_tier4 = ShipAgent:new {
	template = "xwing_tier4",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "bomber",

	experience = 3604.48,

	lootChance = 0.154,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 260,
	maxCredits = 575,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_boss_tier4, "dantooine_miner_boss_tier4")
