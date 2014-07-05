theme_park_imperial_slicer = Creature:new {
	objectName = "",
	socialGroup = "rebel",
	pvpFaction = "rebel",
	faction = "rebel",
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
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_crook_zabrak_female_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "theme_park_loot_datapad", chance = 10000000},
			},
			lootChance = 10000000
		}				
	},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = merge(brawlernovice,marksmannovice)
}

CreatureTemplates:addCreatureTemplate(theme_park_imperial_slicer, "theme_park_imperial_slicer")
