corsec_special_ops_lieutenant = Creature:new {
	objectName = "CorSec Special Ops Lieutenant",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 160,
	chanceHit = 10.000000,
	damageMin = 945,
	damageMax = 1600,
	baseXp = 15170,
	baseHAM = 95000,
	baseHAMmax = 116000,
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_lieutenant, "corsec_special_ops_lieutenant")