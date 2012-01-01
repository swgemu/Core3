giant_mutant_bark_mite = Creature:new {
	objectName = "@mob/creature_names:giant_mutant_bark_mite",
	socialGroup = "Mutant Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {5,5,5,10,10,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 20,
	hideType = "hide_bristley",
	hideAmount = 18,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaattack",""},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_mutant_bark_mite, "giant_mutant_bark_mite")