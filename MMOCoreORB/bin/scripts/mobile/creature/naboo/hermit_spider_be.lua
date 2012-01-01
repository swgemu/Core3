hermit_spider_be = Creature:new {
	objectName = "@mob/creature_names:hermit_spider_be",
	socialGroup = "Hermit Spider",
	pvpFaction = "",
	faction = "",
	level = 1,
	chanceHit = 0.2,
	damageMin = 30,
	damageMax = 40,
	baseXp = 30,
	baseHAM = 50,
	baseHAMmax = 50,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	creatureBitmask = STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_hue.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(hermit_spider_be, "hermit_spider_be")