juvenile_canyon_krayt_dragon = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:juvenile_canyon_krayt",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 122,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	range = 0,
	baseXp = 11577,
	baseHAM = 49000,
	armor = 0,
	resists = {70,70,0,0,10,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 750,
	hideType = "hide_bristley",
	hideAmount = 500,
	boneType = "bone_mammal",
	boneAmount = 410,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_canyon_krayt_dragon, "juvenile_canyon_krayt_dragon")
