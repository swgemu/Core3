female_roba = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:roba_female",
	socialGroup = "Roba",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	range = 0,
	baseXp = 960,
	baseHAM = 3200,
	armor = 0,
	resists = {0,0,0,40,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_roba, "female_roba")
