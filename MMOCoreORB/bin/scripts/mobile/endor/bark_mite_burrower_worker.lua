bark_mite_burrower_worker = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_worker",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 370,
	damageMax = 450,
	baseXp = 4370,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {45,60,-1,80,-1,80,80,30,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"mediumdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_worker, "bark_mite_burrower_worker")