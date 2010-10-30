lesser_prophet_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:lesser_prophet_of_the_dark_side",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 85,
	chanceHit = 0.850000,
	damageMin = 655,
	damageMax = 1020,
	baseXp = 8130,
	baseHAM = 12000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"dark_jedi_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lesser_prophet_of_the_dark_side, "lesser_prophet_of_the_dark_side")