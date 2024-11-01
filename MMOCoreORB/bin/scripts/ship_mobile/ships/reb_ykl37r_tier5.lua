reb_ykl37r_tier5 = ShipAgent:new {
	template = "ykl37r_tier5",
	pilotTemplate = "heavy_tier5",
	shipType = "fighter",

	experience = 13421.77,

	lootChance = 0.26,
	lootRolls = 1,
	lootTable = "space_rebel_tier5",

	minCredits = 465,
	maxCredits = 975,

	aggressive = 0,

	spaceFaction = "rebel",
	alliedFactions = {"nym", "rebel"},
	enemyFactions = {"imperial", "blacksun", "borvo", "hutt", "pirate", "aynat"},
	imperialFactionReward = 96,
	rebelFactionReward = -191,

	color1 = 59,
	color2 = 10,
	texture = 1,
	formationLocation = 2,
	appearance = "rebel_pilot",

	tauntType = "rebel_low",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
}

ShipAgentTemplates:addShipAgentTemplate(reb_ykl37r_tier5, "reb_ykl37r_tier5")
