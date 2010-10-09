minor_gorax = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:minor_gorax",
	socialGroup = "Gorax ",
	pvpFaction = "",
	faction = "",
	level = 131,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	range = 0,
	baseXp = 12424,
	baseHAM = 99000,
	armor = 0,
	resists = {65,65,50,50,50,0,50,50,-1},
	meatType = "meat_",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(minor_gorax, "minor_gorax")
