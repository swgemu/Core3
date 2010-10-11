razor_cat_cub = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:sand_panther_cub",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	range = 0,
	baseXp = 356,
	baseHAM = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 25,
	hideType = "hide_bristley",
	hideAmount = 14,
	boneType = "bone_mammal",
	boneAmount = 12,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(razor_cat_cub, "razor_cat_cub")
