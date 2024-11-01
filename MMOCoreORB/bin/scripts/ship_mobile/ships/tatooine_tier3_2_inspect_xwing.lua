tatooine_tier3_2_inspect_xwing = ShipAgent:new {
	template = "xwing_tier2",
	pilotTemplate = "medium_fighter_tier2",
	shipType = "fighter",

	experience = 440,

	lootChance = 0.176,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rebel_suspect",
	imperialFactionReward = 3,
	rebelFactionReward = -6,
	color2 = 4,
	texture = 1,
	questLoot = "tatooine_tier3_2_inspect",
	formationLocation = 2,
	appearance = "rebel_officer",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tatooine_tier3_2_inspect_xwing, "tatooine_tier3_2_inspect_xwing")
