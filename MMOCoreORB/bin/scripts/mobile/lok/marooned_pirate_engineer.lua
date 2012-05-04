marooned_pirate_engineer = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_engineer",
	socialGroup = "pirate",
	pvpFaction = "pirate",
	faction = "pirate",
	level = 19,
	chanceHit = 0.32,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1609,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,20,5,40,-1,40,-1,-1,-1},
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
		"object/mobile/dressed_marooned_pirate_engr_bith_m.iff",
		"object/mobile/dressed_marooned_pirate_engr_hum_f.iff",
		"object/mobile/dressed_marooned_pirate_engr_hum_m.iff",
		"object/mobile/dressed_marooned_pirate_engr_sull_m.iff",
		"object/mobile/dressed_marooned_pirate_engr1_bith_m.iff",
		"object/mobile/dressed_marooned_pirate_engr1_hum_f.iff",
		"object/mobile/dressed_marooned_pirate_engr1_hum_m.iff",
		"object/mobile/dressed_marooned_pirate_engr1_sull_m.iff"
		},
	lootGroups = {},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(marooned_pirate_engineer, "marooned_pirate_engineer")