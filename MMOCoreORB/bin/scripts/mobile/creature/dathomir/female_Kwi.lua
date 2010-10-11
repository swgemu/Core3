female_Kwi = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "female Kwi",
	socialGroup = "Kwi",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.280000,
	damageMin = 120,
	damageMax = 130,
	range = 25,
	baseXp = 430,
	baseHAM = 450,
	armor = 0,
	resists = {15,15,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 76,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_Kwi, "female_Kwi")
