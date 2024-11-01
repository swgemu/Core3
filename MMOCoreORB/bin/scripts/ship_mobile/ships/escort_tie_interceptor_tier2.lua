escort_tie_interceptor_tier2 = ShipAgent:new {
	template = "tieinterceptor_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_imperial_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -9,
	rebelFactionReward = 5,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_interceptor_tier2, "escort_tie_interceptor_tier2")
