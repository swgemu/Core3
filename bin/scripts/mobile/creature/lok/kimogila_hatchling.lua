kimogila_hatchling = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "kimogila hatchling",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	range = 25,
	baseXp = 2006,
	baseHAM = 4550,
	armor = 0,
	resists = {0,0,0,55,0,0,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_leathery",
	hideAmount = 625,
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
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kimogila_hatchling, "kimogila_hatchling")
