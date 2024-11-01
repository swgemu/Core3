tatooine_tier3_2_inspect_bwing = ShipAgent:new {
	template = "bwing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "fighter",

	experience = 480,

	lootChance = 0.192,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 75,
	maxCredits = 160,

	aggressive = 0,

	spaceFaction = "rebel_suspect",
	imperialFactionReward = 3,
	rebelFactionReward = -6,

	color1 = 42,
	color2 = 9,
	texture = 3,
	questLoot = "tatooine_tier3_2_inspect",
	appearance = "rebel_officer",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tatooine_tier3_2_inspect_bwing, "tatooine_tier3_2_inspect_bwing")
