rebel_surface_marshall = Creature:new {
	objectName = "@mob/creature_names:rebel_surface_marshal",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rebel",
	faction = "rebel",
	level = 21,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {15,20,0,40,-1,40,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_rebel_surface_marshal_moncal_female_01.iff",
		"object/mobile/dressed_rebel_surface_marshal_rodian_male_01.iff",
		"object/mobile/dressed_rebel_surface_marshal_human_male_01.iff",
		"object/mobile/dressed_rebel_surface_marshal_rodian_female_01.iff",
		"object/mobile/dressed_rebel_surface_marshal_twk_male_fat_01.iff",
		"object/mobile/dressed_rebel_surface_marshal_zabrak_male_01.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3200000},
				{group = "holocron_dark", chance = 450000},
				{group = "holocron_light", chance = 450000},
				{group = "rifles", chance = 1180000},
				{group = "pistols", chance = 1180000},
				{group = "carbines", chance = 1180000},
				{group = "melee_weapons", chance = 930000},
				{group = "clothing_attachments", chance = 240000},
				{group = "armor_attachments", chance = 240000},
				{group = "rebel_officer_common", chance = 450000},
				{group = "wearables_common", chance = 500000}
			},
			lootChance = 3000000
		}
	},
	weapons = {"rebel_weapons_heavy"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/military",
	personalityStf = "@hireling/hireling_military",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(rebel_surface_marshall, "rebel_surface_marshall")
