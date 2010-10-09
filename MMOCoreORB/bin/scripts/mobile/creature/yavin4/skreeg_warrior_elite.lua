skreeg_warrior_elite = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:skreeg_warrior_elite",
	socialGroup = "Skreeg",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	range = 0,
	baseXp = 3005,
	baseHAM = 9300,
	armor = 0,
	resists = {-1,75,0,-1,100,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(skreeg_warrior_elite, "skreeg_warrior_elite")
