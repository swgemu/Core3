dragonet = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:dragonet",
	socialGroup = "Dragonet",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	range = 25,
	baseXp = 2914,
	baseHAM = 9100,
	armor = 0,
	resists = {25,40,0,0,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 125,
	hideType = "hide_bristley",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 68,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(dragonet, "dragonet")
