blooming_jax = Creature:new {
	objectName = "@mob/creature_names:blooming_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2730,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {35,35,50,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/blooming_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blooming_jax, "blooming_jax")