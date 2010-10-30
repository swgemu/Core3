fuzzy_jax = Creature:new {
	objectName = "@mob/creature_names:fuzzy_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 140,
	damageMax = 150,
	baseXp = 514,
	baseHAM = 1100,
	baseHAMmax = 1100,
	armor = 0,
	resists = {10,25,10,-1,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 11,
	hideType = "hide_bristley",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/bearded_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fuzzy_jax, "fuzzy_jax")