rebel_smuggler = ShipAgent:new {
	template = "yt1300_tier1",
	pilotTemplate = "heavy_tier1",
	shipType = "fighter",

	experience = 200,

	lootChance = 0.34,
	lootRolls = 1,
	lootTable = "space_rebel_tier1",

	minCredits = 60,
	maxCredits = 120,

	aggressive = 0,

	spaceFaction = "rebel",
	imperialFactionReward = 3,
	rebelFactionReward = -6,

	color1 = 59,
	color2 = 10,
	texture = 5,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_smuggler, "rebel_smuggler")
