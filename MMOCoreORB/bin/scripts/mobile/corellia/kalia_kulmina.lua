kalia_kulmina = Creature:new {
	objectName = "",
	customName = "Kalia Kulmina",
	socialGroup = "",
	pvpFaction = "",
	faction = "",
	level = 100,
	chanceHit = 1,
	damageMin = 645,
	damageMax = 1000,
	baseXp = 9429,
	baseHAM = 24000,
	baseHAMmax = 30000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
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
	weapons = {},
	conversationTemplate = "garmTargetConvo",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(kalia_kulmina, "kalia_kulmina")
