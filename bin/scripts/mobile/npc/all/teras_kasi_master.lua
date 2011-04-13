teras_kasi_master = Creature:new {
	objectName = "@mob/creature_names:teras_kasi_master",
	socialGroup = "Townsperson",
	pvpFaction = "Townsperson",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1609,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {40,0,0,0,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {""},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(teras_kasi_master, "teras_kasi_master")