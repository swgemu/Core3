remmer_carrion_keeper = Creature:new {
	objectName = "@mob/creature_names:remmer_carrion_keeper",
	socialGroup = "Remmer",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 6550,
	armor = 0,
	resists = {30,0,40,-1,-1,-1,50,-1,-1},
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
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(remmer_carrion_keeper, "remmer_carrion_keeper")
