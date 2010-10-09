mutant_rancor = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mutant_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 75,
	chanceHit = 0.700000,
	damageMin = 495,
	damageMax = 700,
	range = 0,
	baseXp = 7207,
	baseHAM = 13500,
	armor = 0,
	resists = {45,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1020,
	hideType = "hide_leathery",
	hideAmount = 901,
	boneType = "bone_mammal",
	boneAmount = 851,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_rancor, "mutant_rancor")
