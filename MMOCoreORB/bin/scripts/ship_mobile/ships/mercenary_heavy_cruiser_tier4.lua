mercenary_heavy_cruiser_tier4 = ShipAgent:new {
	template = "merchant_cruiser_medium_tier4",
	pilotTemplate = "slow_tier4",
	shipType = "fighter",

	experience = 13107.2,

	lootChance = 0.56,
	lootRolls = 1,
	lootTable = "space_pirate_tier4",

	minCredits = 465,
	maxCredits = 950,

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

ShipAgentTemplates:addShipAgentTemplate(mercenary_heavy_cruiser_tier4, "mercenary_heavy_cruiser_tier4")
