marooned_pirate_first_mate = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate_first_mate",
	socialGroup = "pirate",
	faction = "pirate",
	level = 22,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2219,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {20,20,10,40,-1,40,10,-1,-1},
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
		"object/mobile/dressed_marooned_pirate_first_mate_hum_f.iff",
		"object/mobile/dressed_marooned_pirate_first_mate_hum_m.iff",
		"object/mobile/dressed_marooned_pirate_first_mate_nikto_m.iff",
		"object/mobile/dressed_marooned_pirate_first_mate_rod_m.iff",
		"object/mobile/dressed_marooned_pirate_first_mate_tran_m.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "pistols", chance = 2000000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(marooned_pirate_first_mate, "marooned_pirate_first_mate")
