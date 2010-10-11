bark_mite_burrower_queen = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:bark_mite_burrower_queen",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 60,
	chanceHit = 0.550000,
	damageMin = 440,
	damageMax = 590,
	range = 25,
	baseXp = 5830,
	baseHAM = 12000,
	armor = 0,
	resists = {60,50,-1,80,-1,80,80,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "hide_scale",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_queen, "bark_mite_burrower_queen")
