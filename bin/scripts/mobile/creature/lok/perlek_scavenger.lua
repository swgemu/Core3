perlek_scavenger = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:perlek_scavanger",
	socialGroup = "Perlek",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	range = 25,
	baseXp = 831,
	baseHAM = 2700,
	armor = 0,
	resists = {0,0,0,30,30,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 275,
	hideType = "hide_leathery",
	hideAmount = 115,
	boneType = "bone_avian",
	boneAmount = 185,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(perlek_scavenger, "perlek_scavenger")
