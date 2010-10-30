nightsister_initiate = Creature:new {
	objectName = "@mob/creature_names:nightsister_initiate",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 60,
	chanceHit = 0.500000,
	damageMin = 445,
	damageMax = 600,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 0,
	resists = {0,0,0,100,100,100,100,100,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(nightsister_initiate, "nightsister_initiate")