gnarled_bark_mite_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:gnarled_bark_mite_queen",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 1257,
	baseHAM = 5000,
	armor = 0,
	resists = {0,15,-1,0,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 13,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_bark_mite_queen, "gnarled_bark_mite_queen")
