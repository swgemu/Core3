lian_thief = Creature:new {
	objectName = "@mob/creature_names:thief",
	socialGroup = "thug",
	faction = "thug",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 430,
	baseHAM = 1200,
	baseHAMmax = 1400,
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
	pvpBitmask = ATTACKABLE + ENEMY + AGGRESSIVE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_kobola_thief_rodian_male_01.iff",
		"object/mobile/dressed_kobola_thief_rodian_female_01.iff",
		"object/mobile/dressed_binayre_thief_twk_male_01.iff",
		"object/mobile/dressed_binayre_thief_twk_female_01.iff" },
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "wearables_common", chance = 3000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "tailor_components", chance = 1000000},
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(lian_thief, "lian_thief")
