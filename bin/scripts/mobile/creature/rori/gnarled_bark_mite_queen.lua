gnarled_bark_mite_queen = Creature:new {
	objectName = "@mob/creature_names:gnarled_bark_mite_queen",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 18,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,15,-1,0,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 13,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gnarled_bark_mite_queen.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_bark_mite_queen, "gnarled_bark_mite_queen")