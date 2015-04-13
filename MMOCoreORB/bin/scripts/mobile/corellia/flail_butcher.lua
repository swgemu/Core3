flail_butcher = Creature:new {
	objectName = "@mob/creature_names:flail_butcher",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "flail",
	faction = "flail",
	level = 22,
	chanceHit = 0.35,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2219,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mugger.iff",
		"object/mobile/dressed_goon_twk_female_01.iff",
		"object/mobile/dressed_goon_twk_male_01.iff",
		"object/mobile/dressed_gran_thug_male_01.iff",
		"object/mobile/dressed_gran_thug_male_02.iff",
		"object/mobile/dressed_ravager_human_female_01.iff",
		"object/mobile/dressed_ravager_human_male_01.iff",
		"object/mobile/dressed_raider_trandoshan_female_01.iff",
		"object/mobile/dressed_raider_trandoshan_male_01.iff",
		"object/mobile/dressed_ruffian_zabrak_female_01.iff",
		"object/mobile/dressed_criminal_thug_zabrak_male_01.iff",
		"object/mobile/dressed_villain_trandoshan_female_01.iff",
		"object/mobile/dressed_villain_trandoshan_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "wearables_common", chance = 3000000},
				{group = "rifles", chance = 2000000},
				{group = "color_crystals", chance = 1000000},
				{group = "flail_common", chance = 500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(flail_butcher, "flail_butcher")
