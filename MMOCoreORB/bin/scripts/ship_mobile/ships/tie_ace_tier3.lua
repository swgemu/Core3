tie_ace_tier3 = ShipAgent:new {
	template = "tiefighter_tier3",
	pilotTemplate = "light_fighter_tier4",
	shipType = "fighter",

	experience = 1280,

	lootChance = 0.15,
	lootRolls = 1,
	lootTable = "space_imperial_tier4",

	minCredits = 120,
	maxCredits = 294,

	aggressive = 0,

	spaceFaction = "imperial",
	alliedFactions = {"merchant", "civilian", "imperial"},
	enemyFactions = {"rebel", "hutt", "pirate", "nym"},
	imperialFactionReward = -21,
	rebelFactionReward = 11,
	appearance = "imperial_ace",

	tauntType = "imperial",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tie_ace_tier3, "tie_ace_tier3")
