hermit_spider_queen = Creature:new {
	objectName = "@mob/creature_names:hermit_spider_queen",
	socialGroup = "spider",
	faction = "",
	level = 11,
	chanceHit = 0.28,
	damageMin = 80,
	damageMax = 90,
	baseXp = 514,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {120,120,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_queen.iff"},
	scale = 1.4,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"mildpoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(hermit_spider_queen, "hermit_spider_queen")
