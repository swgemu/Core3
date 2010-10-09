crazed_gurk_destroyer = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:crazed_gurk_destroyer",
	socialGroup = "Gurk",
	pvpFaction = "",
	faction = "",
	level = 43,
	chanceHit = 0.440000,
	damageMin = 385,
	damageMax = 480,
	range = 0,
	baseXp = 4279,
	baseHAM = 10700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crazed_gurk_destroyer, "crazed_gurk_destroyer")
