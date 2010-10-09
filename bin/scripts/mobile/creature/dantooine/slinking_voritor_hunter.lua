slinking_voritor_hunter = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:slinking_voritor_hunter",
	socialGroup = "Voritor Lizard",
	pvpFaction = "",
	faction = "",
	level = 57,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	range = 0,
	baseXp = 5555,
	baseHAM = 12000,
	armor = 0,
	resists = {45,45,0,0,0,-1,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 90,
	hideType = "hide_leathery",
	hideAmount = 65,
	boneType = "bone_avian",
	boneAmount = 50,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(slinking_voritor_hunter, "slinking_voritor_hunter")
