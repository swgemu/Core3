first_brigade_infiltrator = Creature:new {
	objectName = "@mob/creature_names:brigade_infiltrator",
	socialGroup = "restuss",
	pvpFaction = "restuss",
	faction = "restuss",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,10,-1,-1},
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
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_brigade_infiltrator_human_male_01.iff",
		"object/mobile/dressed_brigade_infiltrator_human_female_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 4000000},
				{group = "color_crystals", chance = 500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "loot_kits", chance = 3500000}
			},
			lootChance = 4800000
		}					
	},
	weapons = {"rebel_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(first_brigade_infiltrator, "first_brigade_infiltrator")