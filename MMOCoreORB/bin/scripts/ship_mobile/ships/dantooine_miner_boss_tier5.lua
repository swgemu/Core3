dantooine_miner_boss_tier5 = ShipAgent:new {
	template = "xwing_tier5",
	pilotTemplate = "medium_fighter_tier5",
	shipType = "bomber",

	experience = 7381.98,

	lootChance = 0.143,
	lootRolls = 1,
	lootTable = "space_pirate_tier5",

	minCredits = 455,
	maxCredits = 875,

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

ShipAgentTemplates:addShipAgentTemplate(dantooine_miner_boss_tier5, "dantooine_miner_boss_tier5")
