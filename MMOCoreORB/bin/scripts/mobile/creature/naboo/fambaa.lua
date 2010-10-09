fambaa = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:fambaa",
	socialGroup = "Fambaa",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	range = 0,
	baseXp = 3370,
	baseHAM = 9700,
	armor = 0,
	resists = {0,0,0,0,60,60,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 1250,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fambaa, "fambaa")
