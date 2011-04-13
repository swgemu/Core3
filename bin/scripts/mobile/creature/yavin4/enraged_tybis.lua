enraged_tybis = Creature:new {
	objectName = "@mob/creature_names:enraged_tybis",
	socialGroup = "Tybis",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2637,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 220,
	hideType = "hide_bristley",
	hideAmount = 160,
	boneType = "bone_mammal",
	boneAmount = 105,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/tybis.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(enraged_tybis, "enraged_tybis")