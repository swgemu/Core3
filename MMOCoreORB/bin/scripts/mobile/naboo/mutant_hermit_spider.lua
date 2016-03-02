mutant_hermit_spider = Creature:new {
	objectName = "",
	customName = "a mutant hermit spider",
	socialGroup = "spider",
	faction = "",
	level = 7,
	chanceHit = 0.3,
	damageMin = 75,
	damageMax = 95,
	baseXp = 247,
	baseHAM = 300,
	baseHAMmax = 360,
	armor = 0,
	resists = {0,0,110,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 70,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_hue.iff"},
	scale = 1.5,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_hermit_spider, "mutant_hermit_spider")
