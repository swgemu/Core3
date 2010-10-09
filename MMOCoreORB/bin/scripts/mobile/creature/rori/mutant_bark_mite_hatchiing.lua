mutant_bark_mite_hatchiing = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "mutant bark mite hatchiing",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.270000,
	damageMin = 80,
	damageMax = 90,
	range = 0,
	baseXp = 430,
	baseHAM = 1700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 8,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_hatchiing, "mutant_bark_mite_hatchiing")
