deranged_ravisher = Creature:new {
	socialGroup = "Endor Squill",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.390000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3460,
	baseHAM = 9000,
	armor = 0,
	resists = {40,40,0,-1,0,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"mediumdisease",""}
	}
}

