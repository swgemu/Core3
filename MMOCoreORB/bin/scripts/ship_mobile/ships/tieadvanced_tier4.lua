tieadvanced_tier4 = ShipAgent:new {
	template = "tieadvanced_tier4",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 3932.16,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 275,
	maxCredits = 600,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -65,
	rebelFactionReward = 33,
	formationLocation = 3,
	appearance = "imperial_pilot",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tieadvanced_tier4, "tieadvanced_tier4")
