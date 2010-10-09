pouncing_jax = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:pouncing_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 150,
	damageMax = 160,
	range = 0,
	baseXp = 609,
	baseHAM = 1700,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(pouncing_jax, "pouncing_jax")
