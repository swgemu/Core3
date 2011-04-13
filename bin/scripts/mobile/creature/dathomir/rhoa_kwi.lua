rhoa_kwi = Creature:new {
	objectName = "rhoa kwi",
	socialGroup = "Rhoa Kwi",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 3551,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {0,0,0,80,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi, "rhoa_kwi")