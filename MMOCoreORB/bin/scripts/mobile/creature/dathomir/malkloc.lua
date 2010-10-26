malkloc = Creature:new {
	objectName = "@monster_name:malkloc",
	socialGroup = "Malkloc",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.330000,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 6000,
	armor = 0,
	resists = {15,20,0,-1,-1,-1,0,45,-1},
	meatType = "meat_herbivore",
	meatAmount = 1100,
	hideType = "hide_leathery",
	hideAmount = 1200,
	boneType = "bone_mammal",
	boneAmount = 1100,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(malkloc, "malkloc")
