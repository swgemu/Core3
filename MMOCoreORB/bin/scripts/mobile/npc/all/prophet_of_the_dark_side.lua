prophet_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:prophet_of_the_dark_side",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 126,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 11953,
	baseHAM = 44000,
	baseHAMmax = 54000,
	armor = 0,
	resists = {80,80,80,80,80,80,80,80,-1},
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
	lootGroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(prophet_of_the_dark_side, "prophet_of_the_dark_side")