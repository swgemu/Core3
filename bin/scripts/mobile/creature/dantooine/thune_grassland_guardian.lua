thune_grassland_guardian = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:thune_grassland_guardian",
	socialGroup = "Thune",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	range = 0,
	baseXp = 3915,
	baseHAM = 10300,
	armor = 0,
	resists = {45,60,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 135,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(thune_grassland_guardian, "thune_grassland_guardian")
