lords_mistress_tier3 = ShipAgent:new {
	template = "ykl37r_tier3",
	pilotTemplate = "heavy_tier3",
	shipType = "fighter",

	experience = 2560,

	lootChance = 0.3,
	lootRolls = 1,
	lootTable = "cilivian_tier3",

	minCredits = 200,
	maxCredits = 480,

	aggressive = 0,

	spaceFaction = "merchant",
	alliedFactions = {"merchant", "rsf" , "corsec"},

	imperialFactionReward = 0,
	rebelFactionReward = 0,

	color1 = 20,
	color2 = 51,
	texture = 2,

	questLoot = "lords_mistress",
	appearance = "civilian",

	tauntType = "generic",
	tauntAttackChance = 0.1,
	tauntDefendChance = 0.05,
	tauntDieChance = 0.1,
	tauntAggressiveness = 0.05,

	pvpBitmask = ATTACKABLE,
	shipBitmask = NONE,
	optionsBitmask = AIENABLED,

	customShipAiMap = "",

	conversationTemplate = "",
	conversationMobile = "",
	conversationMessage = "", --Too Far Message
}

ShipAgentTemplates:addShipAgentTemplate(lords_mistress_tier3, "lords_mistress_tier3")
