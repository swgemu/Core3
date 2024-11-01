rebel_spysmuggler_tier2 = ShipAgent:new {
	template = "yt1300_tier2",
	pilotTemplate = "heavy_tier2",
	shipType = "bomber",

	experience = 800,

	lootChance = 0.32,
	lootRolls = 1,
	lootTable = "space_rebel_tier2",

	minCredits = 95,
	maxCredits = 240,

	aggressive = 1,

	spaceFaction = "rebel",
	alliedFactions = {"rebel", "civilian"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 10,
	rebelFactionReward = -20,

	color1 = 59,
	color2 = 10,
	texture = 5,
	questLoot = "personnel_dossier",
	appearance = "rebel_pilot",

	tauntType = "rebel",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(rebel_spysmuggler_tier2, "rebel_spysmuggler_tier2")
