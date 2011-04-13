frenzied_pubam = Creature:new {
	objectName = "@mob/creature_names:frenzied_pubam",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 40,
	chanceHit = 0.440000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4006,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {0,0,0,0,0,-1,-1,100,-1},
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

CreatureTemplates:addCreatureTemplate(frenzied_pubam, "frenzied_pubam")