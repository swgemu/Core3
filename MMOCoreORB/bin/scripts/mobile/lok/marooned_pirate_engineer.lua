marooned_pirate_engineer = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_engineer",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "pirate",
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
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
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "carbines", chance = 2000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(marooned_pirate_engineer, "marooned_pirate_engineer")
