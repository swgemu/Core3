scavenger_freighter_tier4 = ShipAgent:new {
	template = "freightermedium_tier4",
	pilotTemplate = "heavy_tier4",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_pirate_tier4",

	minCredits = 16,
	maxCredits = 200,

	aggressive = 0,

	spaceFaction = "pirate",
	appearance = "generic_pirate",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(scavenger_freighter_tier4, "scavenger_freighter_tier4")
