mire_marauder = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mire_marauder",
	socialGroup = "Sludge Panth.",
	pvpFaction = "",
	faction = "",
	level = 56,
	chanceHit = 0.550000,
	damageMin = 445,
	damageMax = 600,
	range = 0,
	baseXp = 5464,
	baseHAM = 10800,
	armor = 0,
	resists = {55,55,0,80,-1,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 150,
	hideType = "hide_leathery",
	hideAmount = 140,
	boneType = "bone_mammal",
	boneAmount = 140,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mire_marauder, "mire_marauder")
