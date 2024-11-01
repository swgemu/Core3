rebel_scout_shuttle = ShipAgent:new {
	template = "freighterlight_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "transport",

	experience = 0,

	lootChance = 0,
	lootRolls = 0,
	lootTable = "space_rebel_tier3",

	minCredits = 90,
	maxCredits = 225,

	aggressive = 0,

	spaceFaction = "rebel",
	rebelFactionReward = -30,
	questLoot = "rebel_plans",
	formationLocation = 1,
	appearance = "rebel_pilot",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_scout_shuttle, "rebel_scout_shuttle")
