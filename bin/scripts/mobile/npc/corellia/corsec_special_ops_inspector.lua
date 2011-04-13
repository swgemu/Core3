corsec_special_ops_inspector = Creature:new {
	objectName = "CorSec Special Ops Inspector",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 150,
	chanceHit = 8.500000,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 14219,
	baseHAM = 81000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {55,55,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_inspector, "corsec_special_ops_inspector")