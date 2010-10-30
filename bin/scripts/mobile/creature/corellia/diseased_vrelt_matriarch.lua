diseased_vrelt_matriarch = Creature:new {
	objectName = "@mob/creature_names:diseased_vrelt_matriarch",
	socialGroup = "Vrelt",
	pvpFaction = "",
	faction = "",
	level = 11,
	chanceHit = 0.280000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 514,
	baseHAM = 900,
	baseHAMmax = 900,
	armor = 0,
	resists = {5,5,0,0,15,0,15,-1,-1},
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
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/vrelt.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"milddisease",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(diseased_vrelt_matriarch, "diseased_vrelt_matriarch")