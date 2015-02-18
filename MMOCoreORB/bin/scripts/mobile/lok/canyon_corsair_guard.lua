canyon_corsair_guard = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_guard",
	socialGroup = "canyon_corsair",
	faction = "canyon_corsair",
	level = 36,
	chanceHit = 0.42,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3642,
	baseHAM = 8900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {25,60,25,-1,-1,-1,25,-1,-1},
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
		"object/mobile/dressed_corsair_guard_hum_f.iff",
		"object/mobile/dressed_corsair_guard_hum_m.iff",
		"object/mobile/dressed_corsair_guard_nikto_m.iff",
		"object/mobile/dressed_corsair_guard_rod_m.iff"
		},
	
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4100000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 400000},
				{group = "melee_two_handed", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 400000},
				{group = "armor_attachments", chance = 400000},
				{group = "canyon_corsair_common", chance = 1500000}
			},
			lootChance = 4000000
		}
	},
	weapons = {"canyon_corsair_weapons"},
	conversationTemplate = "",
	reactionStf = "@npc_reaction/slang",
	attacks = merge(swordsmanmaster,carbineermaster,tkamaster,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_guard, "canyon_corsair_guard")
