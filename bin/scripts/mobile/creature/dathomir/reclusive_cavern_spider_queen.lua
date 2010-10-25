reclusive_cavern_spider_queen = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_recluse_queen",
	socialGroup = "Spider Nightsister ",
	pvpFaction = "",
	faction = "",
	level = 70,
	chanceHit = 0.650000,
	damageMin = 510,
	damageMax = 730,
	range = 0,
	baseXp = 6747,
	baseHAM = 12500,
	armor = 0,
	resists = {60,60,60,50,0,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 45,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareapoison",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(reclusive_cavern_spider_queen, "reclusive_cavern_spider_queen")
