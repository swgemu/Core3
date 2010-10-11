leviasquall = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:leviasquall",
	socialGroup = "Squall",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	range = 0,
	baseXp = 1426,
	baseHAM = 5000,
	armor = 0,
	resists = {15,0,-1,-1,30,30,-1,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 50,
	hideType = "hide_bristley",
	hideAmount = 61,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(leviasquall, "leviasquall")
