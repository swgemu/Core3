nudfuh = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:nudfuh",
	socialGroup = "Nudfuh",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.300000,
	damageMin = 140,
	damageMax = 150,
	range = 0,
	baseXp = 514,
	baseHAM = 1700,
	armor = 0,
	resists = {0,0,0,0,15,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1100,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(nudfuh, "nudfuh")
