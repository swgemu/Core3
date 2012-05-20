mercenary_messenger = Creature:new {
	objectName = "@mob/creature_names:mercenary_messanger",
	socialGroup = "lok_mercenaries",
	pvpFaction = "lok_mercenaries",
	faction = "lok_mercenaries",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {20,0,0,0,0,0,-1,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mercenary_messanger_hum_f.iff",
		"object/mobile/dressed_mercenary_messanger_hum_m.iff",
		"object/mobile/dressed_mercenary_messanger_rod_m.iff",
		"object/mobile/dressed_mercenary_messanger_sullustan_m.iff"
		},
	lootGroups = {},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(mercenary_messenger, "mercenary_messenger")