escort_tie_interceptor_tier5 = ShipAgent:new {
	template = "tieinterceptor_tier5",
	pilotTemplate = "light_fighter_tier5",
	shipType = "fighter",

	experience = 6039.8,

	lootChance = 0.117,
	lootRolls = 1,
	lootTable = "space_imperial_tier5",

	minCredits = 350,
	maxCredits = 750,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -86,
	rebelFactionReward = 43,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_interceptor_tier5, "escort_tie_interceptor_tier5")
