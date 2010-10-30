deranged_squall = Creature:new {
	objectName = "deranged squall",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 714,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {10,0,0,-1,-1,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 15,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/squall.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(deranged_squall, "deranged_squall")