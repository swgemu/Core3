thief = Creature:new {
	objectName = "@mob/creature_names:thief",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "thug",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {
		"object/mobile/dressed_kobola_thief_rodian_male_01.iff",
		"object/mobile/dressed_kobola_thief_rodian_female_01.iff",
		"object/mobile/dressed_binayre_thief_twk_male_01.iff",
		"object/mobile/dressed_binayre_thief_twk_female_01.iff"},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(thief, "thief")