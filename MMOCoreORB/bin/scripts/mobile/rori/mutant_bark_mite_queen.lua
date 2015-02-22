mutant_bark_mite_queen = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_queen",
	socialGroup = "mite",
	faction = "",
	level = 38,
	chanceHit = 0.39,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3824,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {165,165,20,155,155,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "hide_scaley",
	hideAmount = 30,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_burrower_queen.iff"},
	scale = 3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"creatureareableeding",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_queen, "mutant_bark_mite_queen")
