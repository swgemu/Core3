spooky_pubam_spiritmaster = Creature:new {
	objectName = "@mob/creature_names:spooky_pubam_spiritmaster",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 8200,
	baseHAMmax = 10000,
	armor = 0,
	resists = {0,0,0,40,40,40,40,-1,-1},
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

CreatureTemplates:addCreatureTemplate(spooky_pubam_spiritmaster, "spooky_pubam_spiritmaster")