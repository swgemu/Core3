corsec_special_agent = Creature:new {
	objectName = "CorSec Special Agent",
	socialGroup = "Corsec [aggro]",
	pvpFaction = "Corsec [aggro]",
	faction = "",
	level = 105,
	chanceHit = 1.750000,
	damageMin = 670,
	damageMax = 1050,
	baseXp = 9987,
	baseHAM = 29000,
	baseHAMmax = 36000,
	armor = 0,
	resists = {45,45,30,0,80,30,0,35,-1},
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

CreatureTemplates:addCreatureTemplate(corsec_special_agent, "corsec_special_agent")