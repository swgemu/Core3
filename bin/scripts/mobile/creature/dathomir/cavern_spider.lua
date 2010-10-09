cavern_spider = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:cave_gaping_spider",
	socialGroup = "Sp. Nightsister ",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	range = 0,
	baseXp = 2822,
	baseHAM = 8550,
	armor = 0,
	resists = {30,30,0,-1,0,0,-1,-1,-1},
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
		{"mildpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider, "cavern_spider")
