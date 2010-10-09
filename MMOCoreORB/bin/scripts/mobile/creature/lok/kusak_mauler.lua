kusak_mauler = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:kusak_mauler",
	socialGroup = "Kusak",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	range = 0,
	baseXp = 2006,
	baseHAM = 5550,
	armor = 0,
	resists = {0,15,0,0,-1,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 21,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 11,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kusak_mauler, "kusak_mauler")
