haggard_pubam_battlelord = Creature:new {
	objectName = "@mob/creature_names:haggard_pubam_battlelord",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 44,
	chanceHit = 0.500000,
	damageMin = 420,
	damageMax = 550,
	baseXp = 4370,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 0,
	resists = {-1,-1,0,0,0,-1,-1,100,-1},
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

CreatureTemplates:addCreatureTemplate(haggard_pubam_battlelord, "haggard_pubam_battlelord")