cavern_spider = Creature:new {
	objectName = "@mob/creature_names:cave_spider",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {30,30,15,-1,15,15,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider, "cavern_spider")