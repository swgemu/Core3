nightsister_stalker = Creature:new {
	objectName = "@mob/creature_names:nightsister_stalker",
	socialGroup = "Nightsister",
	pvpFaction = "Nightsister",
	faction = "",
	level = 96,
	chanceHit = 0.850000,
	damageMin = 595,
	damageMax = 900,
	baseXp = 9150,
	baseHAM = 20000,
	baseHAMmax = 25000,
	armor = 0,
	resists = {0,100,0,100,100,100,100,100,-1},
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

CreatureTemplates:addCreatureTemplate(nightsister_stalker, "nightsister_stalker")