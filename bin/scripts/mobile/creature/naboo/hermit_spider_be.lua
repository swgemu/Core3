hermit_spider_be = Creature:new {
	objectName = "hermit spider be",
	socialGroup = "Hermit Spider",
	pvpFaction = "",
	faction = "",
	level = 1,
	chanceHit = 0.200000,
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
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	diet = CARNIVORE,

	templates = {"object/mobile/hermit_spider_hue.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(hermit_spider_be, "hermit_spider_be")