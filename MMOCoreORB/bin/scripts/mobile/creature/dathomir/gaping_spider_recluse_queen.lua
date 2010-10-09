gaping_spider_recluse_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:gaping_spider_recluse_queen",
	socialGroup = "Gaping Recluse",
	pvpFaction = "",
	faction = "",
	level = 68,
	chanceHit = 0.650000,
	damageMin = 510,
	damageMax = 730,
	range = 25,
	baseXp = 6563,
	baseHAM = 12500,
	armor = 0,
	resists = {45,65,45,90,-1,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 11,
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
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(gaping_spider_recluse_queen, "gaping_spider_recluse_queen")
