corsec_special_ops_trainee = Creature:new {
	objectName = "CorSec Special Ops Trainee",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 71,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	baseXp = 6839,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {35,35,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_ops_trainee, "corsec_special_ops_trainee")