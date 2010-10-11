armodragon = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:dragonet_armodragon",
	socialGroup = "Dragonet",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 315,
	damageMax = 340,
	range = 25,
	baseXp = 3370,
	baseHAM = 9550,
	armor = 0,
	resists = {25,40,0,0,0,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 125,
	hideType = "hide_bristley",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 68,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(armodragon, "armodragon")
