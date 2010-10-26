torton = Creature:new {
	objectName = "@monster_name:torton",
	socialGroup = "Torton",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2443,
	baseHAM = 6550,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,45,-1},
	meatType = "meat_carnivore",
	meatAmount = 1300,
	hideType = "hide_wooly",
	hideAmount = 1150,
	boneType = "bone_mammal",
	boneAmount = 1300,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(torton, "torton")
