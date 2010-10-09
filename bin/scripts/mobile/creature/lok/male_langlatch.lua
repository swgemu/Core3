male_langlatch = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:langlatch_male",
	socialGroup = "Langlatch",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	range = 0,
	baseXp = 714,
	baseHAM = 2200,
	armor = 0,
	resists = {0,15,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_wooly",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 9,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(male_langlatch, "male_langlatch")
