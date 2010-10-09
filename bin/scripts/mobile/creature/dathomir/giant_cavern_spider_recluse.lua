giant_cavern_spider_recluse = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:cave_gaping_spider_recluse_giant",
	socialGroup = "Spider Nightsister ",
	pvpFaction = "",
	faction = "",
	level = 116,
	chanceHit = 3.100000,
	damageMin = 775,
	damageMax = 1260,
	range = 0,
	baseXp = 11015,
	baseHAM = 33500,
	armor = 0,
	resists = {60,60,60,0,0,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 80,
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
		{"creatureareacombo",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_cavern_spider_recluse, "giant_cavern_spider_recluse")
