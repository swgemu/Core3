first_brigade_officer = Creature:new {
	objectName = "@mob/creature_names:brigade_officer",
	socialGroup = "restuss",
	pvpFaction = "restuss",
	faction = "restuss",
	level = 17,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
		"object/mobile/dressed_brigade_officer_rodian_male_01.iff",
		"object/mobile/dressed_brigade_officer_rodian_female_01.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 7000000},
				{group = "color_crystals", chance = 500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "loot_kit_parts", chance = 500000}
			},
			lootChance = 3200000
		}					
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(first_brigade_officer, "first_brigade_officer")