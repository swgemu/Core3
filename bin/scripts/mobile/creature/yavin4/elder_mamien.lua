elder_mamien = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:mamien_elder",
	socialGroup = "Mamien",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	range = 0,
	baseXp = 1609,
	baseHAM = 5000,
	armor = 0,
	resists = {0,20,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 18,
	hideType = "hide_wooly",
	hideAmount = 18,
	boneType = "bone_mammal",
	boneAmount = 18,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_mamien, "elder_mamien")
