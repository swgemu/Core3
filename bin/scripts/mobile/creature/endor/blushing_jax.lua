blushing_jax = Creature:new {
	objectName = "@mob/creature_names:blushing_jax",
	socialGroup = "Jax",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2730,
	baseHAM = 9200,
	baseHAMmax = 9200,
	armor = 0,
	resists = {35,30,50,-1,-1,-1,-1,-1,-1},
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

	templates = {"object/mobile/blushing_jax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blushing_jax, "blushing_jax")