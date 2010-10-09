famished_sludge_panther = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:famished_sludge_panther",
	socialGroup = "Sludge Panther",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 200,
	damageMax = 210,
	range = 0,
	baseXp = 1609,
	baseHAM = 3900,
	armor = 0,
	resists = {0,20,0,-1,-1,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_leathery",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(famished_sludge_panther, "famished_sludge_panther")
