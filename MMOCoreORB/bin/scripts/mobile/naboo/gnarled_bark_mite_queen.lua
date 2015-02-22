gnarled_bark_mite_queen = Creature:new {
	objectName = "@mob/creature_names:gnarled_bark_mite_queen",
	socialGroup = "mite",
	faction = "",
	level = 18,
	chanceHit = 0.32,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 4500,
	baseHAMmax = 5500,
	armor = 0,
	resists = {0,115,-1,0,-1,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 13,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gnarled_bark_mite_queen.iff"},
	scale = 1.25,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack","stunChance=50"},
		{"milddisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_bark_mite_queen, "gnarled_bark_mite_queen")
