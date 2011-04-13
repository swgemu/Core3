lesser_prophet_of_the_light_side = Creature:new {
	objectName = "Lesser Prophet of the Light Side",
	socialGroup = "Rebel",
	pvpFaction = "Rebel",
	faction = "",
	level = 85,
	chanceHit = 0.850000,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8130,
	baseHAM = 13000,
	baseHAMmax = 16000,
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
	weapons = {"light_jedi_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(lesser_prophet_of_the_light_side, "lesser_prophet_of_the_light_side")