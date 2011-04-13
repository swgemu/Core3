pubam_chieftan = Creature:new {
	objectName = "@mob/creature_names:pubam_chieftan",
	socialGroup = "Pubam",
	pvpFaction = "Pubam",
	faction = "",
	level = 51,
	chanceHit = 0.600000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5007,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {-1,-1,0,0,0,0,0,100,-1},
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

CreatureTemplates:addCreatureTemplate(pubam_chieftan, "pubam_chieftan")