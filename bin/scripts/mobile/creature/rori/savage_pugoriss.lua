savage_pugoriss = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:savage_pugoriss",
	socialGroup = "Pugoriss",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 160,
	damageMax = 170,
	range = 0,
	baseXp = 831,
	baseHAM = 2700,
	armor = 0,
	resists = {0,5,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 350,
	hideType = "hide_leathery",
	hideAmount = 400,
	boneType = "bone_mammal",
	boneAmount = 350,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(savage_pugoriss, "savage_pugoriss")
