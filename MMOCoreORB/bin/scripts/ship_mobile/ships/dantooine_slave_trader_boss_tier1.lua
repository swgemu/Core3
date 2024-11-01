dantooine_slave_trader_boss_tier1 = ShipAgent:new {
	template = "blacksun_heavy_s03_tier2",
	pilotTemplate = "heavy_fighter_tier1",
	shipType = "bomber",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_story_dantooine_slave",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 1,

	spaceFaction = "pirate",
	alliedFactions = {"pirate", "imperial"},
	enemyFactions = {"rebel", "nym", "merchant"},
	color2 = 12,
	texture = 4,
	appearance = "generic_pirate",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_boss_tier1, "dantooine_slave_trader_boss_tier1")
