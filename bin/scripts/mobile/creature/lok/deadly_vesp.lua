deadly_vesp = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:deadly_vesp",
	socialGroup = "Vesp",
	pvpFaction = "",
	faction = "",
	level = 93,
	chanceHit = 0.900000,
	damageMin = 670,
	damageMax = 1050,
	range = 0,
	baseXp = 8871,
	baseHAM = 14500,
	armor = 0,
	resists = {40,40,0,0,0,0,0,0,-1},
	meatType = "meat_reptil",
	meatAmount = 15,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deadly_vesp, "deadly_vesp")
