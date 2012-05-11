senior_prophet_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:senior_prophet_of_the_dark_side",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 138,
	chanceHit = 4.750000,
	damageMin = 920,
	damageMax = 1550,
	baseXp = 13084,
	baseHAM = 50000,
	baseHAMmax = 61000,
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

	templates = {
		"object/mobile/dressed_dark_jedi_human_male_01.iff",
		"object/mobile/dressed_dark_jedi_human_female_01.iff"},
	lootGroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(senior_prophet_of_the_dark_side, "senior_prophet_of_the_dark_side")