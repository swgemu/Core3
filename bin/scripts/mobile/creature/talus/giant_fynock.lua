giant_fynock = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_fynock",
	socialGroup = "Fynock",
	pvpFaction = "",
	faction = "",
	level = 42,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	range = 25,
	baseXp = 4188,
	baseHAM = 11000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 70,
	hideType = "hide_leathery",
	hideAmount = 50,
	boneType = "bone_avian",
	boneAmount = 55,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_fynock, "giant_fynock")
