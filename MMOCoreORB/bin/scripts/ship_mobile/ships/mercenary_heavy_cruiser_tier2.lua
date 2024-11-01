mercenary_heavy_cruiser_tier2 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier2",
	pilotTemplate = "slow_tier2",
	shipType = "fighter",

	experience = 1600,

	lootChance = 0.64,
	lootRolls = 1,
	lootTable = "space_pirate_tier2",

	minCredits = 170,
	maxCredits = 368,

	aggressive = 0,

	spaceFaction = "civilian",

	color1 = 61,
	color2 = 60,
	texture = 4,
	questLoot = "encrypted_documents",
	appearance = "generic_pirate",

	tauntType = "generic_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(mercenary_heavy_cruiser_tier2, "mercenary_heavy_cruiser_tier2")
