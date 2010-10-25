noxious_squill = Creature:new {
	objectName = "@mob/creature_names:noxious_squill",
	socialGroup = "Endor Squill",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.330000,
	damageMin = 180,
	damageMax = 190,
	range = 0,
	baseXp = 1426,
	baseHAM = 5000,
	armor = 0,
	resists = {10,0,0,-1,-1,-1,35,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(noxious_squill, "noxious_squill")
