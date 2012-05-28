mercenary_destroyer = Creature:new {
	objectName = "@mob/creature_names:mercenary_destroyer",
	socialGroup = "lok_mercenaries",
	pvpFaction = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 40,
	chanceHit = 0.43,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4006,
	baseHAM = 8700,
	baseHAMmax = 10700,
	armor = 0,
	resists = {60,40,25,25,25,25,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_destroyer_hum_f.iff",
		"object/mobile/dressed_mercenary_destroyer_hum_m.iff",
		"object/mobile/dressed_mercenary_destroyer_nikto_m.iff",
		"object/mobile/dressed_mercenary_destroyer_wee_m.iff"
		},
	lootGroups = {},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(mercenary_destroyer, "mercenary_destroyer")