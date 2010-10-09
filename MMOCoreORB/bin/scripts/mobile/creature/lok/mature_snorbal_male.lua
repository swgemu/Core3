mature_snorbal_male = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mature_snorbal_male",
	socialGroup = "Snorbalmale",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 305,
	damageMax = 320,
	range = 0,
	baseXp = 3188,
	baseHAM = 9550,
	armor = 0,
	resists = {35,35,0,-1,-1,-1,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 545,
	hideType = "hide_leathery",
	hideAmount = 440,
	boneType = "bone_mammal",
	boneAmount = 400,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mature_snorbal_male, "mature_snorbal_male")
