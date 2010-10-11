giant_decay_mite_hatchliing = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "giant decay mite hatchliing",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	range = 0,
	baseXp = 187,
	baseHAM = 125,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 5,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_hatchliing, "giant_decay_mite_hatchliing")
