quenker = Creature:new {
	objectName = "@monster_name:quenker",
	socialGroup = "Quenker",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	range = 0,
	baseXp = 2219,
	baseHAM = 4550,
	armor = 0,
	resists = {25,25,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(quenker, "quenker")
