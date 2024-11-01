blacksun_freightermedium_tier1 = ShipAgent:new {
	template = "freightermedium_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_blacksun_tier5",

	minCredits = 4,
	maxCredits = 50,

	aggressive = 0,

	spaceFaction = "blacksun",
	appearance = "blacksun",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(blacksun_freightermedium_tier1, "blacksun_freightermedium_tier1")
