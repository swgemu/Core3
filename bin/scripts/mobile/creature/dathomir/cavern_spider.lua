cavern_spider = Creature:new {
	objectName = "@mob/creature_names:cave_gaping_spider",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {30,30,0,-1,0,0,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
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

	templates = {"object/mobile/gaping_spider.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"mildpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cavern_spider, "cavern_spider")