lesser_prophet_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:lesser_prophet_of_the_dark_side",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 85,
	chanceHit = 0.85,
	damageMin = 655,
	damageMax = 1020,
	baseXp = 8130,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {40,40,40,40,40,40,40,40,-1},
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

	templates = {"object/mobile/dressed_dark_jedi_human_male_01.iff"},
	lootGroups = {},
	weapons = {"dark_jedi_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lesser_prophet_of_the_dark_side, "lesser_prophet_of_the_dark_side")