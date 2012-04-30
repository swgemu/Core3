rebel_research_attacker_2_coa3 = Creature:new {
	objectName = "",
	customName = "an Imperial Research Attacker",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 45,
	chanceHit = 0.46,
	damageMin = 365,
	damageMax = 440,
	baseXp = 4461,
	baseHAM = 9600,
	baseHAMmax = 11800,
	armor = 0,
	resists = {0,45,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {},
	weapons = {"imperial_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(rebel_research_attacker_2_coa3, "rebel_research_attacker_2_coa3")