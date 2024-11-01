crystal_smuggler_heavy_tier4 = ShipAgent:new {
	template = "blacksun_transport_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier2",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "pirate",
	questLoot = "glowing_crystals",
	appearance = "coynite_pilot",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_heavy_tier4, "crystal_smuggler_heavy_tier4")
