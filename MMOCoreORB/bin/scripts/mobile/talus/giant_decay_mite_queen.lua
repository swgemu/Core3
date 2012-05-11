giant_decay_mite_queen = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_queen",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.35,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {40,40,10,10,10,-1,10,-1,-1},
	meatType = "meat_insect",
	meatAmount = 28,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mediumdisease",""},
		{"mediumpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_queen, "giant_decay_mite_queen")