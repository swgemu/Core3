hanadak_ancient = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:hanadak_ancient",
	socialGroup = "Hanadak",
	pvpFaction = "",
	faction = "",
	level = 41,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	range = 0,
	baseXp = 4097,
	baseHAM = 10300,
	armor = 0,
	resists = {0,0,-1,100,100,100,-1,-1,-1},
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
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(hanadak_ancient, "hanadak_ancient")
