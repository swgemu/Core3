sentry_hermit_spider = Creature:new {
	objectName = "@mob/creature_names:sentry_hermit_spider",
	socialGroup = "Hermit Spider",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 405,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(sentry_hermit_spider, "sentry_hermit_spider")