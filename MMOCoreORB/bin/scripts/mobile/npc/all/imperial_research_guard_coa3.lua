imperial_research_guard_coa3 = Creature:new {
	objectName = "",
	customName = "Imperial Research Guard",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(imperial_research_guard_coa3, "imperial_research_guard_coa3")