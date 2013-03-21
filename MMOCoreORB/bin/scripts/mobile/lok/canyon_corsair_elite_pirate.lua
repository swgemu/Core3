canyon_corsair_elite_pirate = Creature:new {
	objectName = "@mob/creature_names:canyon_corsair_pirate_elite",
	socialGroup = "canyon_corsair",
	pvpFaction = "canyon_corsair",
	faction = "canyon_corsair",
	level = 42,
	chanceHit = 0.44,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4188,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {30,70,30,30,-1,30,30,-1,-1},
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
		"object/mobile/dressed_corsair_pirate_elite_hum_f.iff",
		"object/mobile/dressed_corsair_pirate_elite_hum_m.iff",
		"object/mobile/dressed_corsair_pirate_elite_nikto_m.iff",
		"object/mobile/dressed_corsair_pirate_elite_wee_m.iff",
		"object/mobile/dressed_corsair_pirate_elite_zab_m.iff"
		},
	
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "tailor_components", chance = 1000000},
				{group = "color_crystals", chance = 400000},
				{group = "crystals_good", chance = 400000},
				{group = "melee_two_handed", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 450000},
				{group = "armor_attachments", chance = 450000}
			},
			lootChance = 4000000
		}
	},
	weapons = {"canyon_corsair_weapons"},
	conversationTemplate = "",
	attacks = merge(swordsmanmaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(canyon_corsair_elite_pirate, "canyon_corsair_elite_pirate")
