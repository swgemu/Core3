bewitching_pubam_dark_shaman = Creature:new {
	objectName = "@mob/creature_names:bewitching_pubam_dark_shaman",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,0,0,40,40,-1,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(bewitching_pubam_dark_shaman, "bewitching_pubam_dark_shaman")