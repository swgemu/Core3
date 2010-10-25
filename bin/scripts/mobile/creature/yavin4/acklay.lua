acklay = Creature:new {
	objectName = "@mob/creature_names:geonosian_acklay_bunker_boss",
	socialGroup = "Geon. Monster",
	pvpFaction = "",
	faction = "",
	level = 157,
	chanceHit = 9.250000,
	damageMin = 935,
	damageMax = 1580,
	range = 0,
	baseXp = 14884,
	baseHAM = 107000,
	armor = 0,
	resists = {30,45,55,55,45,0,0,0,-1},
	meatType = "meat_",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"creatureareacombo",""}
	}
}

CreatureTemplates:addCreatureTemplate(acklay, "acklay")
