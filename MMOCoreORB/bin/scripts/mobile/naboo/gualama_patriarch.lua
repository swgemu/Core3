gualama_patriarch = Creature:new {
	objectName = "@mob/creature_names:gualama_patriarch",
	socialGroup = "gualama",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.29,
	damageMin = 120,
	damageMax = 130,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {20,10,20,20,20,0,0,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama_patriarch.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gualama_patriarch, "gualama_patriarch")