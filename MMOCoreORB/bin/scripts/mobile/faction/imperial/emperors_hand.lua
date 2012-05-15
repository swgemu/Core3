emperors_hand = Creature:new {
	objectName = "@mob/creature_names:emperors_hand",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 252,
	chanceHit = 23.5,
	damageMin = 1395,
	damageMax = 2500,
	baseXp = 24081,
	baseHAM = 261000,
	baseHAMmax = 320000,
	armor = 0,
	resists = {90,90,90,90,90,90,90,90,-1},
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
		"object/mobile/dressed_emperors_hand_human_male_01.iff",
		"object/mobile/dressed_emperors_hand_human_male_02.iff",
		"object/mobile/dressed_emperors_hand_human_female_01.iff",
		"object/mobile/dressed_emperors_hand_zabrak_male_01.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(emperors_hand, "emperors_hand")