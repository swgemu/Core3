dwarf_eopie = Creature:new {
	objectName = "@mob/creature_names:dwarf_eopie",
	socialGroup = "Eopie",
	pvpFaction = "",
	faction = "",
	level = 3,
	chanceHit = 0.230000,
	damageMin = 35,
	damageMax = 45,
	range = 0,
	baseXp = 62,
	baseHAM = 100,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 230,
	hideType = "hide_leathery",
	hideAmount = 180,
	boneType = "bone_mammal",
	boneAmount = 110,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(dwarf_eopie, "dwarf_eopie")
