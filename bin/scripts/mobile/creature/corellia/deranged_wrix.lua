deranged_wrix = Creature:new {
	objectName = "deranged wrix",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1102,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {15,15,0,45,-1,0,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 55,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/deranged_wrix.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_wrix, "deranged_wrix")