angler = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:angler",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	range = 0,
	baseXp = 2006,
	baseHAM = 6550,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 4,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"strongpoison",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(angler, "angler")
