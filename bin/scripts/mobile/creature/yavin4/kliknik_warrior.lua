kliknik_warrior = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:kliknik_warrior",
	socialGroup = "Kliknik",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	range = 25,
	baseXp = 2443,
	baseHAM = 6000,
	armor = 0,
	resists = {30,30,0,0,0,0,0,-1,-1},
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
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kliknik_warrior, "kliknik_warrior")
