tatooine_tier3_2_inspect_awing = ShipAgent:new {
	template = "awing_tier2",
	pilotTemplate = "light_fighter_tier2",
	shipType = "fighter",

	experience = 360,

	lootChance = 0.144,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 65,
	maxCredits = 130,

	aggressive = 0,

	spaceFaction = "rebel_suspect",
	imperialFactionReward = 3,
	rebelFactionReward = -5,

	color1 = 63,
	color2 = 3,
	texture = 3,
	questLoot = "tatooine_tier3_2_inspect",
	appearance = "rebel_officer",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(tatooine_tier3_2_inspect_awing, "tatooine_tier3_2_inspect_awing")
