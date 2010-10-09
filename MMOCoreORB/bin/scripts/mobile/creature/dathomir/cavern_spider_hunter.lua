cavern_spider_hunter = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:cave_gaping_spider_hunter",
	socialGroup = "Sp. Nightsister ",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.460000,
	damageMin = 390,
	damageMax = 490,
	range = 25,
	baseXp = 4552,
	baseHAM = 10550,
	armor = 0,
	resists = {40,40,60,15,-1,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider_hunter, "cavern_spider_hunter")
