crimson_razor_cat = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:crimson_sand_panther",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.390000,
	damageMin = 305,
	damageMax = 320,
	range = 0,
	baseXp = 3005,
	baseHAM = 8550,
	armor = 0,
	resists = {35,35,-1,-1,0,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crimson_razor_cat, "crimson_razor_cat")
