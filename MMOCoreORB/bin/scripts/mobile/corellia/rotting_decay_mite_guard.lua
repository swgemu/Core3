rotting_decay_mite_guard = Creature:new {
	objectName = "@mob/creature_names:rotting_pustule_guard",
	socialGroup = "mite",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 714,
	baseHAM = 1200,
	baseHAMmax = 1400,
	armor = 0,
	resists = {0,0,0,0,0,0,10,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/decay_mite.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"mediumdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(rotting_decay_mite_guard, "rotting_decay_mite_guard")