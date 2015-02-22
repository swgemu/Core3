hermit_spider_guard = Creature:new {
	objectName = "@mob/creature_names:hermit_spider_guard",
	socialGroup = "spider",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 0,
	resists = {110,110,0,0,0,110,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_hue.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(hermit_spider_guard, "hermit_spider_guard")
