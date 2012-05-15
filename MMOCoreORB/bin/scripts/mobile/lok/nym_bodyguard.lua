nym_bodyguard = Creature:new {
	objectName = "@mob/creature_names:nym_bodyguard",
	socialGroup = "nym",
	pvpFaction = "nym",
	faction = "nym",
	level = 28,
	chanceHit = 0.37,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2914,
	baseHAM = 8100,
	baseHAMmax = 9900,
	armor = 1,
	resists = {15,15,15,15,40,15,-1,-1,-1},
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

	templates = {"object/mobile/dressed_nym_bodyguard_rod_m.iff",
				"object/mobile/dressed_nym_bodyguard_hum_m.iff",
				"object/mobile/dressed_nym_bodyguard_hum_f.iff"},
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

CreatureTemplates:addCreatureTemplate(nym_bodyguard, "nym_bodyguard")