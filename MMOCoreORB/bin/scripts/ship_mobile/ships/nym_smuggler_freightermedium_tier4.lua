nym_smuggler_freightermedium_tier4 = ShipAgent:new {
	template = "freightermedium_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_nym_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "nym",
	appearance = "nym",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(nym_smuggler_freightermedium_tier4, "nym_smuggler_freightermedium_tier4")
