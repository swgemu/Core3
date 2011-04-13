diminutive_bounding_jax = Creature:new {
	objectName = "@mob/creature_names:jax_bounding_dwarf",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 187,
	baseHAM = 75,
	baseHAMmax = 75,
	armor = 0,
	resists = {10,10,-1,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(diminutive_bounding_jax, "diminutive_bounding_jax")