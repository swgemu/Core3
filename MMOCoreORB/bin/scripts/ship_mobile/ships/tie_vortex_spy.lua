tie_vortex_spy = ShipAgent:new {
	template = "tiefighter_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3276.8,

	lootChance = 0.14,
	lootRolls = 1,
	lootTable = "space_rebel_tier4",

	minCredits = 225,
	maxCredits = 525,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "nym"},
	enemyFactions = {"imperial", "blacksun"},
	imperialFactionReward = 27,
	rebelFactionReward = -54,
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tie_vortex_spy, "tie_vortex_spy")
