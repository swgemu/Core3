freighterheavy_rebel_tier3 = ShipAgent:new {
	template = "freighterheavy_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -30,
	questLoot = "general_cargo",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterheavy_rebel_tier3, "freighterheavy_rebel_tier3")
