nym_guard_strong = Creature:new {
	objectName = "@mob/creature_names:nym_guard_strong",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 9,
	chanceHit = 0.27,
	damageMin = 80,
	damageMax = 90,
	baseXp = 356,
	baseHAM = 675,
	baseHAMmax = 825,
	armor = 1,
	resists = {15,15,15,15,40,-1,-1,-1,-1},
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

	templates = {"object/mobile/dressed_nym_guard_strong_hum_f.iff", 
				"object/mobile/dressed_nym_guard_strong_rod_m.iff",
				"object/mobile/dressed_nym_guard_strong_nikto_m.iff",
				"object/mobile/dressed_nym_guard_strong_hum_m.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 6500000},
				{group = "nyms_common", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 500000}
			},
			lootChance = 3500000
		}
	},
	weapons = {"pirate_weapons_medium"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(nym_guard_strong, "nym_guard_strong")