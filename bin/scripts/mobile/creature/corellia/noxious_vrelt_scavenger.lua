noxious_vrelt_scavenger = Creature:new {
	objectName = "@mob/creature_names:noxious_vrelt_scavenger",
	socialGroup = "Vrelt",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 10,
	boneType = "bone_mammal",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/noxious_vrelt_scavenger.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(noxious_vrelt_scavenger, "noxious_vrelt_scavenger")