escort_tie_advanced_tier3 = ShipAgent:new {
	template = "tieadvanced_tier3",
	pilotTemplate = "light_fighter_tier3",
	shipType = "fighter",

	experience = 1536,

	lootChance = 0.18,
	lootRolls = 1,
	lootTable = "space_imperial_tier3",

	minCredits = 160,
	maxCredits = 353,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"imperial"},
	imperialFactionReward = -30,
	rebelFactionReward = 15,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(escort_tie_advanced_tier3, "escort_tie_advanced_tier3")
