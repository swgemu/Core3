dune_lizard = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:dune_lizard",
	socialGroup = "Dune Lizard",
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
	resists = {0,15,0,45,-1,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 85,
	hideType = "hide_bristley",
	hideAmount = 50,
	boneType = "bone_mammal",
	boneAmount = 35,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + STALKER + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dune_lizard, "dune_lizard")
