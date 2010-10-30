tybis_youth = Creature:new {
	objectName = "@mob/creature_names:tybis_youth",
	socialGroup = "Tybis",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1257,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 200,
	hideType = "hide_bristley",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 100,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/tybis_youth.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(tybis_youth, "tybis_youth")