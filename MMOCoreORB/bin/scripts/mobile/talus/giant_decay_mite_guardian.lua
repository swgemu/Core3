giant_decay_mite_guardian = Creature:new {
	objectName = "@mob/creature_names:giant_decay_mite_royal_guardian",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.33,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2443,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {30,30,5,5,5,-1,-1,-1,-1},
	meatType = "meat_insect",
	meatAmount = 22,
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

	aiTemplate = "default",

	templates = {"object/mobile/decay_mite.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mildpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_decay_mite_guardian, "giant_decay_mite_guardian")