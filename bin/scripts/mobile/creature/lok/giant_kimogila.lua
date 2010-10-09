giant_kimogila = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:giant_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 139,
	chanceHit = 5.500000,
	damageMin = 875,
	damageMax = 1460,
	range = 0,
	baseXp = 13178,
	baseHAM = 72500,
	armor = 0,
	resists = {35,80,0,80,0,0,100,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 1450,
	hideType = "hide_leathery",
	hideAmount = 1350,
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
		{"creatureareaknockdown","knockdownChance=30"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_kimogila, "giant_kimogila")
