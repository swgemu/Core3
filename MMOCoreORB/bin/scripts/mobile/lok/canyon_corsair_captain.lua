canyon_corsair_captain = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_captain",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "canyon_corsair",
	faction = "canyon_corsair",
	level = 50,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4916,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {20,40,5,5,-1,5,5,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_corsair_captain_hum_m.iff",
		"object/mobile/dressed_corsair_captain_nikto_m.iff",
		"object/mobile/dressed_corsair_captain_wee_m.iff",
		"object/mobile/dressed_corsair_captain_zab_m.iff"
	},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3650000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 400000},
				{group = "melee_two_handed", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 450000},
				{group = "armor_attachments", chance = 450000},
				{group = "canyon_corsair_common", chance = 1350000},
				{group = "wearables_uncommon", chance = 500000},
			},
			lootChance = 4500000
		}
	},
	weapons = {"canyon_corsair_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(swordsmanmaster,carbineermaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_captain, "canyon_corsair_captain")
