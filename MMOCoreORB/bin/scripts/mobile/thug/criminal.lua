criminal = Creature:new {
	objectName = "@mob/creature_names:criminal",
	socialGroup = "thug",
	pvpFaction = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_criminal_thug_human_male_01.iff",
					"object/mobile/dressed_criminal_thug_bothan_female_01.iff",
					"object/mobile/dressed_goon_twk_male_01.iff",
					"object/mobile/dressed_robber_twk_female_01.iff",
					"object/mobile/dressed_goon_twk_female_01.iff",
					"object/mobile/dressed_robber_human_female_01.iff",
					"object/mobile/dressed_villain_trandoshan_male_01.iff",
					"object/mobile/dressed_criminal_thug_bothan_male_01.iff",
					"object/mobile/dressed_villain_trandoshan_female_01.iff"
					},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "pistols", chance = 1000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000}
			},
			lootChance = 2200000
		}
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster,brawlernovice)
}

CreatureTemplates:addCreatureTemplate(criminal, "criminal")
