civshuttle_cor_tier3_pilot_capture = ShipAgent:new {
	template = "transport_science_tier3",
	pilotTemplate = "slow_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_civilian_tier1",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "civilian",
	questLoot = "cor_priv_tier3_capture_pilot",
	appearance = "civilian",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(civshuttle_cor_tier3_pilot_capture, "civshuttle_cor_tier3_pilot_capture")
