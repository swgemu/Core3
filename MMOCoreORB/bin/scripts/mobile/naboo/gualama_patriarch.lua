gualama_patriarch = Creature:new {
	objectName = "@mob/creature_names:gualama_patriarch",
	socialGroup = "gualama",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {115,115,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 250,
	hideType = "hide_wooly",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 120,
	milk = 0,
	tamingChance = 0,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama_patriarch.iff"},
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(gualama_patriarch, "gualama_patriarch")
