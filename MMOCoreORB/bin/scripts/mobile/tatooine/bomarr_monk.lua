bomarr_monk = Creature:new {
	objectName = "@mob/creature_names:bomarr_monk",
	socialGroup = "jabba",
	pvpFaction = "jabba",
	faction = "jabba",
	level = 21,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {15,15,0,0,0,-1,0,-1,-1},
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
	creatureBitmask = NONE,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/bomarr_monk_spider_droid.iff"},
	lootGroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(bomarr_monk, "bomarr_monk")