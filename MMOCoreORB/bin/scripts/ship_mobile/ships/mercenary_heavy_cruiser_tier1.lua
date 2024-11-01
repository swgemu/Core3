mercenary_heavy_cruiser_tier1 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier1",
	pilotTemplate = "slow_tier1",
	shipType = "fighter",

	experience = 400,

	lootChance = 0.68,
	lootRolls = 1,
	lootTable = "space_pirate_tier1",

	minCredits = 70,
	maxCredits = 140,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_heavy_cruiser_tier1, "mercenary_heavy_cruiser_tier1")
