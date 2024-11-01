hutt_transport = ShipAgent:new {
	template = "hutt_transport_tier3",
	pilotTemplate = "slow_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_hutt_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 1,

	spaceFaction = "hutt",
	questLoot = "hutt_smuggler",
	appearance = "hutt",

	tauntType = "hutt_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(hutt_transport, "hutt_transport")
