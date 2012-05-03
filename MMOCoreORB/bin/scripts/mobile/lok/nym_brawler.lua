nym_brawler = Creature:new {
	objectName = "@mob/creature_names:nym_brawler",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {45,10,50,15,15,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_nym_brawler_hum_f.iff",
				"object/mobile/dressed_nym_brawler_hum_m.iff",
				"object/mobile/dressed_nym_brawler_nikto_m.iff",
				"object/mobile/dressed_nym_brawler_rod_f.iff",
				"object/mobile/dressed_nym_brawler_rod_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "nyms_common", chance = 2500000},
				{group = "pistols", chance = 2500000},
				{group = "carbines", chance = 2500000},
				{group = "tailor_components", chance = 2500000}
			},
			lootChance = 6500000
		}
	},
	weapons = {"rebel_weapons_medium"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nym_brawler, "nym_brawler")