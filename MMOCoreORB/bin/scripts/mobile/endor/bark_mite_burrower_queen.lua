bark_mite_burrower_queen = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_queen",
	socialGroup = "mite",
	faction = "",
	level = 60,
	chanceHit = 0.55,
	damageMin = 440,
	damageMax = 590,
	baseXp = 5830,
	baseHAM = 11000,
	baseHAMmax = 13000,
	armor = 1,
	resists = {160,150,-1,180,-1,180,180,10,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_burrower_queen.iff"},
	scale = 1.2,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_queen, "bark_mite_burrower_queen")
