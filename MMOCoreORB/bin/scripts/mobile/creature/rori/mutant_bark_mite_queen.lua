mutant_bark_mite_queen = Creature:new {
	objectName = "@mob/creature_names:mutant_bark_mite_queen",
	socialGroup = "Mut. Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.39,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3824,
	baseHAM = 8500,
	baseHAMmax = 10300,
	armor = 0,
	resists = {65,65,20,55,55,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 35,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_burrower_queen.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareableeding",""},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(mutant_bark_mite_queen, "mutant_bark_mite_queen")