crystal_smuggler_heavy = ShipAgent:new {
	template = "blacksun_transport_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "pirate",
	questLoot = "glowing_crystals",
	appearance = "coynite_pilot",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(crystal_smuggler_heavy, "crystal_smuggler_heavy")
