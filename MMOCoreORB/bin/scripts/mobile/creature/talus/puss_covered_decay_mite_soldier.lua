puss_covered_decay_mite_soldier = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:puss_covered_decay_mite_soldier",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	range = 25,
	baseXp = 831,
	baseHAM = 2200,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(puss_covered_decay_mite_soldier, "puss_covered_decay_mite_soldier")
