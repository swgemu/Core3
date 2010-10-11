squill = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:squill",
	socialGroup = "Squill",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	range = 0,
	baseXp = 1257,
	baseHAM = 3900,
	armor = 0,
	resists = {10,10,0,0,-1,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 6,
	hideType = "hide_leathery",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(squill, "squill")
