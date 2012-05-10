first_brigade_trooper = Creature:new {
	objectName = "@mob/creature_names:brigade_trooper",
	socialGroup = "restuss",
	pvpFaction = "restuss",
	faction = "restuss",
	level = 6,
	chanceHit = 0.25,
	damageMin = 50,
	damageMax = 55,
	baseXp = 147,
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
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_brigade_trooper_bith_male_01.iff",
		"object/mobile/dressed_brigade_trooper_bith_female_01.iff"},
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
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(first_brigade_trooper, "first_brigade_trooper")