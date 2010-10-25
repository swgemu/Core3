rotten_gut_remmer_king = Creature:new {
	objectName = "@mob/creature_names:rotten_gut_remmer_king",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 37,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	range = 0,
	baseXp = 3733,
	baseHAM = 9800,
	armor = 0,
	resists = {55,35,60,0,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_bristley",
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
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rotten_gut_remmer_king, "rotten_gut_remmer_king")
