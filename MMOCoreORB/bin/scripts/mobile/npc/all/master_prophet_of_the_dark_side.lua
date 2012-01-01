master_prophet_of_the_dark_side = Creature:new {
	objectName = "@mob/creature_names:master_prophet_of_the_dark_side",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 168,
	chanceHit = 8.5,
	damageMin = 1120,
	damageMax = 1950,
	baseXp = 15933,
	baseHAM = 81000,
	baseHAMmax = 99000,
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(master_prophet_of_the_dark_side, "master_prophet_of_the_dark_side")