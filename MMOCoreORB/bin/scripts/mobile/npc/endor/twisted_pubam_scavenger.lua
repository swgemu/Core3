twisted_pubam_scavenger = Creature:new {
	objectName = "@mob/creature_names:twisted_pubam_scavenger",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,-1,-1,-1,-1},
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

CreatureTemplates:addCreatureTemplate(twisted_pubam_scavenger, "twisted_pubam_scavenger")