dantooine_slave_trader_transport_tier3 = ShipAgent:new {
	template = "blacksun_transport_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_dantooine_slave",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(dantooine_slave_trader_transport_tier3, "dantooine_slave_trader_transport_tier3")
