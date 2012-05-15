meatlump_loon = Creature:new {
	objectName = "@mob/creature_names:meatlump_loon",
	socialGroup = "meatlump",
	pvpFaction = "meatlump",
	faction = "meatlump",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
		"object/mobile/dressed_gran_thug_male_01.iff",
		"object/mobile/dressed_gran_thug_male_02.iff",
		"object/mobile/dressed_criminal_thug_aqualish_female_01.iff",
		"object/mobile/dressed_criminal_thug_aqualish_female_02.iff",
		"object/mobile/dressed_criminal_thug_aqualish_male_01.iff",
		"object/mobile/dressed_criminal_thug_aqualish_male_02.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4500000},
				{group = "loot_kits", chance = 4500000},
				{group = "color_crystals", chance = 500000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"pirate_weapons_light"},
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(meatlump_loon, "meatlump_loon")
