crystal_smuggler_heavy_tier5 = ShipAgent:new {
	template = "blacksun_transport_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier3",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "pirate",
	questLoot = "glowing_crystals",
	appearance = "coynite_pilot",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_heavy_tier5, "crystal_smuggler_heavy_tier5")
