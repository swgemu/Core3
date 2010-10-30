roba_boar = Creature:new {
	objectName = "roba boar",
	socialGroup = "Roba",
	pvpFaction = "",
	faction = "",
	level = 50,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4825,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {35,35,0,60,-1,60,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/roba.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(roba_boar, "roba_boar")