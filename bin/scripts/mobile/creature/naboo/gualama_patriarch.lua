gualama_patriarch = Creature:new {
	objectName = "gualama patriarch",
	socialGroup = "Gualama",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 609,
	baseHAM = 1700,
	baseHAMmax = 1700,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 250,
	hideType = "hide_wooly",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 120,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama_patriarch.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gualama_patriarch, "gualama_patriarch")