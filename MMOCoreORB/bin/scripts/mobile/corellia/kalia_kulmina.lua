kalia_kulmina = Creature:new {
	objectName = "",
	customName = "Kalia Kulmina",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2219,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 264,
	diet = HERBIVORE,
	templates = {
		"object/mobile/dressed_kobola_assassin_zabrak_female_01.iff"
	},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "garmTargetConvo",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(kalia_kulmina, "kalia_kulmina")
