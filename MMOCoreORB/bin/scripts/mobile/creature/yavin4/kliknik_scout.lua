kliknik_scout = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:kliknik_scout",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 240,
	damageMax = 250,
	range = 25,
	baseXp = 2730,
	baseHAM = 8000,
	armor = 0,
	resists = {35,20,0,30,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_scaley",
	hideAmount = 4,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_scout, "kliknik_scout")
