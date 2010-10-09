mountain_worrt = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mountain_worrt",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.340000,
	damageMin = 200,
	damageMax = 210,
	range = 25,
	baseXp = 1803,
	baseHAM = 5000,
	armor = 0,
	resists = {0,30,0,35,35,-1,-1,-1,-1},
	meatType = "meat_reptilian",
	meatAmount = 4,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0.000000,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_worrt, "mountain_worrt")
