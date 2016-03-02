bark_mite_burrower_worker = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_worker",
	socialGroup = "mite",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {145,160,-1,180,-1,180,180,30,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_hue.iff"},
	scale = 1.05,
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_worker, "bark_mite_burrower_worker")
