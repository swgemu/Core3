malkloc_bull = Creature:new {
	objectName = "@mob/creature_names:malkloc_bull",
	socialGroup = "Malkloc",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2822,
	baseHAM = 9100,
	armor = 0,
	resists = {35,35,0,-1,-1,-1,0,50,-1},
	meatType = "meat_herbivore",
	meatAmount = 1400,
	hideType = "hide_leathery",
	hideAmount = 1500,
	boneType = "bone_mammal",
	boneAmount = 1200,
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
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(malkloc_bull, "malkloc_bull")
