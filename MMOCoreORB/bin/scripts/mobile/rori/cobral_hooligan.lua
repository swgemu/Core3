cobral_hooligan = Creature:new {
	objectName = "",
	customName = "a Neo-Cobral Hooligan",
	socialGroup = "cobral",
	pvpFaction = "cobral",
	faction = "cobral",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_cobral_hooligan_bith_male_01.iff",
		"object/mobile/dressed_cobral_hooligan_bith_female_01.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(cobral_hooligan, "cobral_hooligan")