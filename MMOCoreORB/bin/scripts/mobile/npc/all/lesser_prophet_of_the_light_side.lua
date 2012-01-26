lesser_prophet_of_the_light_side = Creature:new {
	objectName = "@mob/creature_names:lesser_prophet_of_the_dark_side",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 85,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8130,
	baseHAM = 13000,
	baseHAMmax = 16000,
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

	templates = {"object/mobile/dressed_jedi_trainer_old_human_male_01.iff"},
	lootgroups = {},
	weapons = {"light_jedi_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lesser_prophet_of_the_light_side, "lesser_prophet_of_the_light_side")