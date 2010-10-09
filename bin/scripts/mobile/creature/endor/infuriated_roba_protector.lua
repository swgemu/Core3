infuriated_roba_protector = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "infuriated roba protector",
	socialGroup = "Roba",
	pvpFaction = "",
	faction = "",
	level = 57,
	chanceHit = 0.550000,
	damageMin = 420,
	damageMax = 550,
	range = 0,
	baseXp = 5555,
	baseHAM = 12500,
	armor = 0,
	resists = {35,35,0,20,0,20,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(infuriated_roba_protector, "infuriated_roba_protector")
