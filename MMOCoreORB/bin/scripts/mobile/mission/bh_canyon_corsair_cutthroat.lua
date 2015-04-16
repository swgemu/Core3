bh_canyon_corsair_cutthroat = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_cutthroat",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "canyon_corsair",
	faction = "canyon_corsair",
	level = 35,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3551,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {20,45,20,20,-1,20,20,-1,-1},
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
		"object/mobile/dressed_corsair_cutthroat_hum_f.iff",
		"object/mobile/dressed_corsair_cutthroat_hum_m.iff",
		"object/mobile/dressed_corsair_cutthroat_wee_m.iff",
		"object/mobile/dressed_corsair_cutthroat_zab_m.iff"
	},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3150000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 400000},
				{group = "melee_two_handed", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 450000},
				{group = "armor_attachments", chance = 450000},
				{group = "canyon_corsair_common", chance = 1350000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 4500000
		},
		{
			groups = {
				{group = "color_crystals", chance = 1500000},
				{group = "crystals_poor", chance = 1000000},
				{group = "crystals_good", chance = 1000000},
				{group = "melee_two_handed", chance = 1500000},
				{group = "carbines", chance = 1500000},
				{group = "pistols", chance = 1500000},
				{group = "clothing_attachments", chance = 1000000},
				{group = "armor_attachments", chance = 1000000}
			},
			lootChance = 6000000
		}
	},
	weapons = {"canyon_corsair_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(swordsmanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(bh_canyon_corsair_cutthroat, "bh_canyon_corsair_cutthroat")
