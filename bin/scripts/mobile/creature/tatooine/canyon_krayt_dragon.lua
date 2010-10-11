canyon_krayt_dragon = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:canyon_krayt_dragon",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 275,
	chanceHit = 27.250000,
	damageMin = 1520,
	damageMax = 2750,
	range = 0,
	baseXp = 26356,
	baseHAM = 356500,
	armor = 0,
	resists = {60,60,60,60,20,60,60,60,-1},
	meatType = "meat_carnivore",
	meatAmount = 1250,
	hideType = "hide_bristley",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 675,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(canyon_krayt_dragon, "canyon_krayt_dragon")
