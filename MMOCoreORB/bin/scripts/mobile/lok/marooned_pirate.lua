marooned_pirate = Creature:new {
	objectName = "@mob/creature_names:marooned_pirate",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_marooned_pirate_bith_m.iff",
		"object/mobile/dressed_marooned_pirate_hum_f.iff",
		"object/mobile/dressed_marooned_pirate_hum_m.iff",
		"object/mobile/dressed_marooned_pirate_nikto_m.iff",
		"object/mobile/dressed_marooned_pirate_rod_f.iff",
		"object/mobile/dressed_marooned_pirate_rod_m.iff",
		"object/mobile/dressed_marooned_pirate_tran_m.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3000000},
				{group = "wearables_common", chance = 2000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
				{group = "melee_weapons", chance = 2000000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(marooned_pirate, "marooned_pirate")
