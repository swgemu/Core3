gringy_pubam_laborer = Creature:new {
	objectName = "gringy Pubam laborer",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 45,
	chanceHit = 0.470000,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4461,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 0,
	resists = {15,35,0,0,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(gringy_pubam_laborer, "gringy_pubam_laborer")