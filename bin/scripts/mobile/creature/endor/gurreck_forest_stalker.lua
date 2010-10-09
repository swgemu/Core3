gurreck_forest_stalker = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:woodland_gurreck",
	socialGroup = "Gurreck",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.390000,
	damageMin = 320,
	damageMax = 350,
	range = 0,
	baseXp = 3188,
	baseHAM = 9000,
	armor = 0,
	resists = {25,50,0,0,-1,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gurreck_forest_stalker, "gurreck_forest_stalker")
