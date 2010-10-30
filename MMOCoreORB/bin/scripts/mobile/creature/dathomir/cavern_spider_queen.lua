cavern_spider_queen = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider_queen",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4552,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {60,60,40,25,0,-1,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 40,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gaping_spider_queen.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider_queen, "cavern_spider_queen")