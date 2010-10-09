stoneskin_hanadak = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:stoneskin_hanadak",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 139,
	chanceHit = 4.750000,
	damageMin = 720,
	damageMax = 1150,
	range = 0,
	baseXp = 13178,
	baseHAM = 97500,
	armor = 0,
	resists = {90,100,65,100,100,100,75,80,-1},
	meatType = "meat_carnivore",
	meatAmount = 40,
	hideType = "hide_bristley",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(stoneskin_hanadak, "stoneskin_hanadak")
