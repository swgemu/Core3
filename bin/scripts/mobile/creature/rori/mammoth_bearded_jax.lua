mammoth_bearded_jax = Creature:new {
	objectName = "@mob/creature_names:mammoth_bearded_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,20,40,0,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/mammoth_bearded_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mammoth_bearded_jax, "mammoth_bearded_jax")