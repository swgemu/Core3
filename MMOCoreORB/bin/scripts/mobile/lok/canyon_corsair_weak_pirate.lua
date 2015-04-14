canyon_corsair_weak_pirate = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_pirate_weak",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "canyon_corsair",
	faction = "canyon_corsair",
	level = 29,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {25,20,20,20,20,-1,-1,-1,-1},
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
		"object/mobile/dressed_corsair_pirate_weak_hum_f.iff",
		"object/mobile/dressed_corsair_pirate_weak_hum_m.iff",
		"object/mobile/dressed_corsair_pirate_weak_rod_m.iff"},

	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3980000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_okay", chance = 400000},
				{group = "melee_two_handed", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 350000},
				{group = "armor_attachments", chance = 350000},
				{group = "canyon_corsair_common", chance = 1720000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"canyon_corsair_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(swordsmanmaster,carbineermaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_weak_pirate, "canyon_corsair_weak_pirate")
