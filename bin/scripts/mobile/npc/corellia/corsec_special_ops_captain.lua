corsec_special_ops_captain = Creature:new {
	objectName = "CorSec Special Ops Captain",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 171,
	chanceHit = 11.500000,
	damageMin = 995,
	damageMax = 1700,
	baseXp = 16220,
	baseHAM = 110000,
	baseHAMmax = 134000,
	armor = 0,
	resists = {65,65,30,0,80,30,0,35,-1},
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
	weapons = {"ranged_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(corsec_special_ops_captain, "corsec_special_ops_captain")