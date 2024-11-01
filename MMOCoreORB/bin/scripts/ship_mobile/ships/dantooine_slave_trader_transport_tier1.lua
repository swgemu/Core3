dantooine_slave_trader_transport_tier1 = ShipAgent:new {
	template = "blacksun_transport_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_dantooine_slave",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_transport_tier1, "dantooine_slave_trader_transport_tier1")
