reb_transport_tier5 = ShipAgent:new {
	template = "rebel_shuttle_tier5",
	pilotTemplate = "heavy_fighter_tier5",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 1,
	lootTable = "space_rebel_tier5",

	minCredits = 500,
	maxCredits = 1050,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -50,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_transport_tier5, "reb_transport_tier5")
