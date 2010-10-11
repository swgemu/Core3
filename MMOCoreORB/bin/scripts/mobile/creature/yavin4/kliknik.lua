kliknik = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:kliknik",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	range = 25,
	baseXp = 1257,
	baseHAM = 4550,
	armor = 0,
	resists = {20,0,0,-1,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
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
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik, "kliknik")
