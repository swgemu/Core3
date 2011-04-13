bearded_jax = Creature:new {
	objectName = "@monster_name:bearded_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 430,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,5,30,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 15,
	hideType = "hide_bristley",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/bearded_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bearded_jax, "bearded_jax")