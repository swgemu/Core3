escort_tie_interceptor_tier3 = ShipAgent:new {
	template = "tieinterceptor_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1152,

	lootChance = 0.135,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 105,
	maxCredits = 264,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -23,
	rebelFactionReward = 12,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_interceptor_tier3, "escort_tie_interceptor_tier3")
