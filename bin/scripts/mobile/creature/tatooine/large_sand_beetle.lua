large_sand_beetle = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:large_sand_beetle",
	socialGroup = "Gt. Sand Beet.",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	range = 0,
	baseXp = 3005,
	baseHAM = 9100,
	armor = 0,
	resists = {35,30,0,0,-1,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(large_sand_beetle, "large_sand_beetle")
