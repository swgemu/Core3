corsec_special_ops_comissioner = Creature:new {
	objectName = "CorSec Special Ops Comissioner",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 226,
	chanceHit = 19.750000,
	damageMin = 1270,
	damageMax = 2250,
	baseXp = 21533,
	baseHAM = 208000,
	baseHAMmax = 254000,
	armor = 0,
	resists = {85,85,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_comissioner, "corsec_special_ops_comissioner")