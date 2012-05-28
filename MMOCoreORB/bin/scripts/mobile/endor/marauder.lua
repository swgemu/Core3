marauder = Creature:new {
	objectName = "@mob/creature_names:marauder",
	socialGroup = "endor_marauder",
	pvpFaction = "endor_marauder",
	faction = "endor_marauder",
	level = 44,
	chanceHit = 0.47,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9000,
	baseHAMmax = 11900,
	armor = 0,
	resists = {0,0,0,0,-1,-1,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {
			"object/mobile/dressed_marauder.iff",
			"object/mobile/dressed_marauder_male.iff",
			"object/mobile/dressed_marauder_male_02.iff",
			"object/mobile/dressed_marauder_male_03.iff",
			"object/mobile/dressed_marauder_female.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(marauder, "marauder")