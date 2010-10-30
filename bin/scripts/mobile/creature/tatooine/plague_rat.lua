plague_rat = Creature:new {
	objectName = "@mob/creature_names:womprat_plague",
	socialGroup = "Womprat",
	pvpFaction = "",
	faction = "",
	level = 12,
	chanceHit = 0.290000,
	damageMin = 130,
	damageMax = 140,
	baseXp = 514,
	baseHAM = 1300,
	baseHAMmax = 1300,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_wild",
	meatAmount = 4,
	hideType = "hide_leathery",
	hideAmount = 3,
	boneType = "bone_mammal",
	boneAmount = 2,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/womp_rat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(plague_rat, "plague_rat")