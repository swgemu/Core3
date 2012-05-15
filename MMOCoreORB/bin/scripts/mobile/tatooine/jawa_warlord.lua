jawa_warlord = Creature:new {
	objectName = "@mob/creature_names:jawa_warlord",
	socialGroup = "jawa",
	pvpFaction = "jawa",
	faction = "jawa",
	level = 12,
	chanceHit = 0.29,
	damageMin = 130,
	damageMax = 140,
	baseXp = 609,
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/jawa_male.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 5000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 300000},
				{group = "pistols", chance = 1600000},
				{group = "rifles", chance = 1600000},
				{group = "carbines", chance = 1100000}
			},
			lootChance = 5500000
		}				
	},
	weapons = {"novice_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmannovice)
}

CreatureTemplates:addCreatureTemplate(jawa_warlord, "jawa_warlord")
