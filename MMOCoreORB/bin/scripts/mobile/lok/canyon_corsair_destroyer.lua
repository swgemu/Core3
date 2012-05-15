canyon_corsair_destroyer = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_destroyer",
	socialGroup = "canyon_corsair",
	pvpFaction = "canyon_corsair",
	faction = "canyon_corsair",
	level = 40,
	chanceHit = 0.43,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4006,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {25,60,25,25,-1,25,25,-1,-1},
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
		"object/mobile/dressed_corsair_destroyer_hum_f.iff",
		"object/mobile/dressed_corsair_destroyer_hum_m.iff",
		"object/mobile/dressed_corsair_destroyer_wee_m.iff",
		"object/mobile/dressed_corsair_destroyer_zab_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_destroyer, "canyon_corsair_destroyer")