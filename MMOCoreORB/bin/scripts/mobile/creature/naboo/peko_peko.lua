peko_peko = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:peko_peko",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	range = 0,
	baseXp = 609,
	baseHAM = 2200,
	armor = 0,
	resists = {0,0,25,0,0,0,0,-1,-1},
	meatType = "meat_avian",
	meatAmount = 105,
	hideType = "hide_wooly",
	hideAmount = 40,
	boneType = "bone_avian",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(peko_peko, "peko_peko")
