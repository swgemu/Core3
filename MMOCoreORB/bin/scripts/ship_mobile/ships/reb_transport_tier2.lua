reb_transport_tier2 = ShipAgent:new {
	template = "rebel_shuttle_tier2",
	pilotTemplate = "heavy_fighter_tier2",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier2",

	minCredits = 18,
	maxCredits = 230,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -20,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_transport_tier2, "reb_transport_tier2")
