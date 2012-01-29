stresstest_shuttleloc_barker = Creature:new {
	objectName = "",
	customName = "Official Stress Test Informant",
	socialGroup = "Townsperson",
	pvpFaction = "",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,
	
	templates = {"object/mobile/dressed_ajuva_vanasterin.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(stresstest_shuttleloc_barker, "stresstest_shuttleloc_barker")