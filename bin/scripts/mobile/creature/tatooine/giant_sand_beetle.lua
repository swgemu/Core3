giant_sand_beetle = Creature:new {
	objectName = "@mob/creature_names:giant_sand_beetle",
	socialGroup = "Giant Sand Beetle",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3097,
	baseHAM = 9300,
	armor = 0,
	resists = {0,35,0,0,-1,-1,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "hide_scaley",
	hideAmount = 20,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_sand_beetle, "giant_sand_beetle")
