enhanced_gaping_spider = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:geonosian_gaping_spider_fire",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 108,
	chanceHit = 2.500000,
	damageMin = 715,
	damageMax = 1140,
	range = 25,
	baseXp = 10267,
	baseHAM = 35500,
	armor = 0,
	resists = {50,0,-1,95,-1,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enhanced_gaping_spider, "enhanced_gaping_spider")
