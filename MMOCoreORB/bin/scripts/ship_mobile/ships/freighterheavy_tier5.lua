freighterheavy_tier5 = ShipAgent:new {
	template = "freighterheavy_tier5",
	pilotTemplate = "slow_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_story_all_freighter",

	minCredits = 20,
	maxCredits = 250,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"rsf", "corsec"},
	questLoot = "general_cargo",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(freighterheavy_tier5, "freighterheavy_tier5")
