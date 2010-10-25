domestic_bol_mount = Creature:new {
	objectName = "@mob/creature_names:domestic_bol_mount",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 260,
	damageMax = 270,
	range = 0,
	baseXp = 3005,
	baseHAM = 9600,
	armor = 0,
	resists = {35,0,-1,0,0,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 300,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domestic_bol_mount, "domestic_bol_mount")
