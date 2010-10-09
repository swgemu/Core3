rancor_youth = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:rancor_youth",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 365,
	damageMax = 440,
	range = 0,
	baseXp = 4370,
	baseHAM = 9900,
	armor = 0,
	resists = {35,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 700,
	hideType = "hide_leathery",
	hideAmount = 753,
	boneType = "bone_mammal",
	boneAmount = 653,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(rancor_youth, "rancor_youth")
