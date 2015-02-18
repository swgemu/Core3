ragtag_loon = Creature:new {
	objectName = "@mob/creature_names:ragtag_loon",
	socialGroup = "ragtag",
	faction = "thug",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_mugger.iff",
		"object/mobile/dressed_goon_twk_female_01.iff",
		"object/mobile/dressed_goon_twk_male_01.iff",
		"object/mobile/dressed_gran_thug_male_01.iff",
		"object/mobile/dressed_gran_thug_male_02.iff",
		"object/mobile/dressed_commoner_old_human_male_01.iff",
		"object/mobile/dressed_commoner_old_human_female_02.iff",
		"object/mobile/dressed_commoner_naboo_twilek_male_02.iff",
		"object/mobile/dressed_commoner_naboo_moncal_male_01.iff",
		"object/mobile/dressed_commoner_tatooine_rodian_female_03.iff",
		"object/mobile/dressed_commoner_old_human_female_01.iff",
		"object/mobile/dressed_commoner_old_human_male_02.iff",
		"object/mobile/dressed_commoner_tatooine_aqualish_female_07.iff"
		},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "crystals_poor", chance = 500000},
				{group = "tailor_components", chance = 1000000}
			},
			lootChance = 3200000
		}
	},
	weapons = {"pirate_weapons_light"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(ragtag_loon, "ragtag_loon")
