smashball_bully = Creature:new {
	objectName = "@mob/creature_names:smashball_bully",
	socialGroup = "smashball",
	pvpFaction = "smashball",
	faction = "smashball",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_goon_twk_female_01.iff",
		"object/mobile/dressed_goon_twk_male_01.iff",
		"object/mobile/dressed_crook_zabrak_female_01.iff",
		"object/mobile/dressed_crook_zabrak_male_01.iff",
		"object/mobile/dressed_desperado_bith_female_01.iff",
		"object/mobile/dressed_desperado_bith_male_01.iff",
		"object/mobile/dressed_hoodlum_zabrak_female_01.iff",
		"object/mobile/dressed_hoodlum_zabrak_male_01.iff",
		"object/mobile/dressed_hooligan_rodian_female_01.iff",
		"object/mobile/dressed_hooligan_rodian_male_01.iff"},
	lootGroups = {
      	{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "loot_kits", chance = 3500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(smashball_bully, "smashball_bully")
