crystal_smuggler_heavy_tier2 = ShipAgent:new {
	template = "blacksun_transport_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "pirate",
	questLoot = "glowing_crystals",
	appearance = "coynite_pilot",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_heavy_tier2, "crystal_smuggler_heavy_tier2")
