elder_hanadak_matriarch = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:elder_hanadak_matriarch",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	range = 0,
	baseXp = 3551,
	baseHAM = 9800,
	armor = 0,
	resists = {0,0,-1,80,80,80,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 35,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_hanadak_matriarch, "elder_hanadak_matriarch")
