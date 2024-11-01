tatooine_tier3_2_inspect_ywing = ShipAgent:new {
	template = "ywing_tier2",
	pilotTemplate = "bomber_tier2",
	shipType = "fighter",

	experience = 420,

	lootChance = 0.168,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 70,
	maxCredits = 140,

	aggressive = 0,

	spaceFaction = "rebel_suspect",
	imperialFactionReward = 3,
	rebelFactionReward = -6,
	color2 = 4,
	texture = 1,
	questLoot = "tatooine_tier3_2_inspect",
	appearance = "rebel_officer",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tatooine_tier3_2_inspect_ywing, "tatooine_tier3_2_inspect_ywing")
