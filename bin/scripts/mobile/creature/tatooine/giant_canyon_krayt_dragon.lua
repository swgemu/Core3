giant_canyon_krayt_dragon = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_canyon_krayt_dragon",
	socialGroup = "Krayt Dragon",
	pvpFaction = "",
	faction = "",
	level = 300,
	chanceHit = 30.000000,
	damageMin = 1645,
	damageMax = 3000,
	range = 0,
	baseXp = 28549,
	baseHAM = 428000,
	armor = 0,
	resists = {70,70,70,70,30,70,70,70,-1},
	meatType = "meat_carnivore",
	meatAmount = 1500,
	hideType = "hide_bristley",
	hideAmount = 870,
	boneType = "bone_mammal",
	boneAmount = 805,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_canyon_krayt_dragon, "giant_canyon_krayt_dragon")
